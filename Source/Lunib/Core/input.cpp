#include "input.h"
#include "Platform/GLFW/glfw_input.h"
#include "Lunib/Events/key_event.h"
#include "Lunib/Events/mouse_event.h"



namespace Lunib
{
    Input* Input::Create(Window* p_window)
    {
        return new GLFWInput(p_window);
    }

    bool Input::IsKeyPressed(Event &p_event, int p_keyCode)
    {
		bool isPressed = false;
		p_event.Dispatch<KeyPressedEvent>([&](KeyPressedEvent& p_KeyEvent)
		{
			if (p_KeyEvent.GetKeyCode() == p_keyCode)
				isPressed = true;

			return isPressed;
		});

		return isPressed;
    }

    bool Input::IsMouseButtonPressed(Event &p_event, int p_button)
    {
		bool isPressed = false;
		p_event.Dispatch<MouseButtonPressedEvent>([&](MouseButtonPressedEvent& p_ButtonEvent)
		{
			if (p_ButtonEvent.GetMouseButton() == p_button)
				isPressed = true;

			return isPressed;
		});

		return isPressed;
    }


} // Lunib