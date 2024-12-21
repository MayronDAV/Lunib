#define LUNIB_MATH_STRING_OPERATOR
#include "Lunib/lunib.h"

// std
#include <iostream>
#include <format>


static bool s_Running 			= true;
static Lunib::Input* s_Input 	= nullptr;


void EventCallback(Lunib::Event& p_event)
{
	std::cout << p_event << "\n";
		
	p_event.Dispatch<Lunib::WindowCloseEvent>([&](Lunib::WindowCloseEvent&) -> bool
	{
		s_Running = false;
		return true;
	});
}


int main()
{
	Lunib::WindowSpecification wspec 	= {};
	wspec.Title 						= "Sandbox";
	wspec.Width 						= 800;
	wspec.Height 						= 600;
	wspec.Maximize 						= true;
	wspec.Resizable 					= true;
	wspec.Mode 							= Lunib::WindowMode::Windowed;

	Lunib::Window* window 				= Lunib::Window::Create(wspec);

	window->SetEventCallback(EventCallback);

	s_Input 							= Lunib::Input::Create(window);

	while(s_Running)
	{
		window->OnUpdate();
	}

	delete s_Input;
	delete window;
}