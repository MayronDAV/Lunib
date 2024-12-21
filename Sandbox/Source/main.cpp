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

	while(s_Running)
	{
		Lunib::RendererAPI::Get().ClearColor({ 1.0f }, false);

		s_Window->OnUpdate();
	}

	delete s_Input;
	delete s_Window;
}