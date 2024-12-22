#define LUNIB_MATH_STRING_OPERATOR
#include "Lunib/lunib.h"

// std
#include <iostream>
#include <format>



static bool s_Running 			= true;
static Lunib::Window* s_Window 	= nullptr;
static Lunib::Input* s_Input 	= nullptr;


static void EventCallback(Lunib::Event& p_event)
{
	if (p_event == Lunib::EventType::WindowClose)
	{
		s_Running = false;
	}

	if (s_Input->IsKeyPressed(p_event, Lunib::Key::F11))
	{
		if (s_Window->GetMode() != Lunib::WindowMode::Fullscreen)
			s_Window->SetWindowMode(Lunib::WindowMode::Fullscreen, true, true);
		else
			s_Window->SetWindowMode(Lunib::WindowMode::Windowed, false, true);
	}
}


static const char* vertex_shader_text =
"#version 450\n"
"layout(location = 0) in vec2 a_pos;\n"
"layout(location = 0) uniform mat4 MVP;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(a_pos, 0.0, 1.0);\n"
"}\n";
 
static const char* fragment_shader_text =
"#version 450\n"
"layout(location = 0) out vec4 o_color;\n"
"layout(location = 1) uniform vec3 u_color;\n"
"void main()\n"
"{\n"
"    o_color = vec4(u_color, 1.0);\n"
"}\n";


int main()
{
	Lunib::WindowSpecification wspec 	= {};
	wspec.Title 						= "Sandbox";
	wspec.Width 						= 800;
	wspec.Height 						= 600;
	wspec.Maximize 						= false;
	wspec.Resizable 					= true;
	wspec.Mode 							= Lunib::WindowMode::Windowed;

	s_Window 							= Lunib::Window::Create(wspec);
	s_Window->SetEventCallback(EventCallback);


	s_Input 							= Lunib::Input::Create(s_Window);
	
	auto shader 						= Lunib::ShaderLibrary::Get("teste", { { Lunib::ShaderType::Vertex, vertex_shader_text }, { Lunib::ShaderType::Fragment, fragment_shader_text } });

	while(s_Running)
	{
		Lunib::RendererAPI::Get().ClearColor({ 1.0f }, false);

		s_Window->OnUpdate();
	}

	Lunib::ShaderLibrary::Release();
	delete s_Input;
	delete s_Window;
}