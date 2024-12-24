#define LUNIB_MATH_STRING_OPERATOR
#include "Lunib/lunib.h"

// std
#include <iostream>

using namespace Lunib;

static bool s_Running 			= true;
static Window* s_Window 		= nullptr;
static uint32_t s_Width 		= 800;
static uint32_t s_Height 		= 600;
static Input* s_Input 			= nullptr;
static bool s_Reload 			= false;

static const char *vertex_shader_text = "#version 450 core\n"
    "layout (location = 0) in vec3 inPos;\n"
	"layout (location = 1) in vec2 inTexcoord;\n"
	"uniform mat4 u_MVP;\n"
	"layout (location = 0) out vec2 outTexcoord;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = u_MVP * vec4(inPos, 1.0);\n"
	"	outTexcoord = inTexcoord;\n"
    "}\0";
 
static const char* fragment_shader_text = "#version 450 core\n"
	"layout (location = 0) out vec4 o_color;\n"
	"layout (location = 0) in vec2 inTexcoord;\n"
	"uniform sampler2D u_Texture;\n"
	"void main()\n"
	"{\n"
	"    o_color = texture(u_Texture, inTexcoord);\n"
	"}\0";



static void EventCallback(Event& p_event)
{
	if (p_event == EventType::WindowClose)
	{
		s_Running = false;
	}

	if (s_Input->IsKeyPressed(p_event, Key::F11))
	{
		if (s_Window->GetMode() != WindowMode::Fullscreen)
		{
			s_Window->SetWindowMode(WindowMode::Fullscreen, true, true);
			s_Reload = true;
		}
		else
		{
			s_Window->SetWindowMode(WindowMode::Windowed, false, true);
			s_Reload = true;
		}
	}
}



static void ProcessInputs(double p_dt, Vec3& p_position)
{
	Vec3 direction(0.0f);

	if (s_Input->IsKeyPressed(Key::W))
		direction.y = 1.0f;
	if (s_Input->IsKeyPressed(Key::S))
		direction.y = -1.0f;
	if (s_Input->IsKeyPressed(Key::A))
		direction.x = -1.0f;
	if (s_Input->IsKeyPressed(Key::D))
		direction.x = 1.0f;

	if (direction != Vec3(0.0f))
	{
		direction = Math::Normalize(direction);
	}

	p_position += direction * 1.5f * float(p_dt);
}

static Mat4 CalcProjection()
{
    float size = 20.0f;
    float aspect = float(s_Window->GetWidth()) / float(s_Window->GetHeight());

    float orthoLeft   = -size * 0.5f;
    float orthoRight  =  size * 0.5f;
    float orthoBottom = -size * 0.5f / aspect;
    float orthoTop    =  size * 0.5f / aspect;

    return Math::Ortho(orthoLeft, orthoRight, orthoBottom, orthoTop, -1.0f, 1.0f);
}



int main()
{
	WindowSpecification wspec 	= {};
	wspec.Title 						= "Sandbox";
	wspec.Width 						= 800;
	wspec.Height 						= 600;
	wspec.Maximize 						= false;
	wspec.Resizable 					= true;
	wspec.Mode 							= WindowMode::Windowed;

	s_Window 							= Window::Create(wspec);
	s_Window->SetEventCallback(EventCallback);

	if (!LInit())
		throw std::runtime_error("Failed on Lunib init!");

	s_Input 							= Input::Create(s_Window);
	
	auto shader							= ShaderLibrary::Get("simple_shader", { { ShaderType::Vertex, vertex_shader_text }, { ShaderType::Fragment, fragment_shader_text } });

	// Vertex Array
	auto vertexArray = VertexArray::Create();

	const float quad_vertices[] = {
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
		-1.0f,  1.0f, 0.0f, 0.0f, 1.0f
	};

	// Vertex Buffer
	auto vertexBuffer = VertexBuffer::Create(quad_vertices, sizeof(quad_vertices));
	vertexBuffer->SetLayout({ 
		{ DataType::Float3, "inPos" } ,
		{ DataType::Float2, "inTexcoord" } 
	});

	vertexArray->SetVertexBuffer(vertexBuffer);

	// Index Buffer
	uint32_t indices[] = { 0, 1, 2, 2, 3, 0 };
	auto indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

	vertexArray->SetIndexBuffer(indexBuffer);

	Vec3 position = { 0.0f, 0.0f, 0.0f };

	double lastFrameTime = Clock::GetTime();

	Mat4 projection = CalcProjection();

	//FpsCalculator fps;

	Texture2D* container 	= LoadTexture2D("Resources/container.jpg");
	Texture2D* wall 		= LoadTexture2D("Resources/wall.jpg");

	while(s_Running)
	{
		if (s_Reload)
		{
			RendererAPI::Release();
			RendererAPI::Init();
			Destroy(vertexArray);
			Destroy(vertexBuffer);
			Destroy(indexBuffer);
			Destroy(s_Input);	
			s_Input = Input::Create(s_Window);
			shader  = ShaderLibrary::Reload("simple_shader", { { ShaderType::Vertex, vertex_shader_text }, { ShaderType::Fragment, fragment_shader_text } });

			vertexArray = VertexArray::Create();

			vertexBuffer = VertexBuffer::Create(quad_vertices, sizeof(quad_vertices));
			vertexBuffer->SetLayout({ 
				{ DataType::Float3, "aPos" } 
			});

			vertexArray->SetVertexBuffer(vertexBuffer);

			// Index Buffer
			indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

			vertexArray->SetIndexBuffer(indexBuffer);

			s_Reload = false;
		}

		// Timing

		double time = Clock::GetTime();
		double dt = time - lastFrameTime;
		lastFrameTime = time;

		// input

		ProcessInputs(dt, position);

		// math

		if (s_Width != s_Window->GetWidth() || s_Height != s_Window->GetHeight())
		{
			projection 	= CalcProjection();
			s_Width 	= s_Window->GetWidth();
			s_Height 	= s_Window->GetHeight();
		}


		Mat4 model 	= Math::Translate(position);
		Mat4 view 	= Math::Inverse(model);

		// draw
		RendererAPI::Get().SetViewport(0, 0, s_Window->GetWidth(), s_Window->GetHeight());

		RendererAPI::Get().ClearColor({ 0.0f, 1.0f, 0.0f, 1.0f });

		shader->Bind();

		container->Bind();
		{
			shader->SetMat4("u_MVP", projection * view * model);
			shader->SetVec3("u_Color", { 1.0f, 0.0f, 0.0f });

			RendererAPI::Get().DrawIndexed(DrawType::Triangles, vertexArray);
		}
		container->Unbind();

		wall->Bind();
		for (float x = 0.0f; x < 5.0f; x++)
		{
			for (float y = 0.0f; y < 5.0f; y++)
			{
				Mat4 tile = Math::Translate(Vec3{ x * 0.17f, y * 0.23f, 0.0f });
				shader->SetMat4("u_MVP", projection * view * tile);
				shader->SetVec3("u_Color", { 1.0f, 1.0f, 0.0f });

				RendererAPI::Get().DrawIndexed(DrawType::Triangles, vertexArray);
			}
		}
		wall->Unbind();

		shader->Unbind();

		// swap buffer

		s_Window->OnUpdate();
		
		//fps.Calculate();
	}

	Destroy(container);
	Destroy(wall);
	Destroy(vertexArray);
	Destroy(vertexBuffer);
	Destroy(indexBuffer);
	Destroy(s_Input);
	LShutdown();
	Destroy(s_Window);
}