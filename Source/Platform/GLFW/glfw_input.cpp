#include "glfw_input.h"

// lib
#include <GLFW/glfw3.h>


namespace Lunib
{
    GLFWInput::GLFWInput(Window *p_window)
    {
        m_Window = (GLFWwindow*)p_window->GetNativeWindow();
    }

    bool GLFWInput::IsKeyPressed(int p_keycode) const
    {
		auto state = glfwGetKey(m_Window, p_keycode);
		return state == GLFW_PRESS;
    }

    bool GLFWInput::IsMouseButtonPressed(int p_button) const
    {
		auto state = glfwGetMouseButton(m_Window, p_button);
		return state == GLFW_PRESS;
    }

    Vec2 GLFWInput::GetMousePosition() const
    {
		double xpos, ypos;
		glfwGetCursorPos(m_Window, &xpos, &ypos);

		return Vec2((float)xpos, (float)ypos);
    }

    float GLFWInput::GetMouseX() const
    {
        return GetMousePosition().x;
    }

    float GLFWInput::GetMouseY() const
    {
        return GetMousePosition().y;
    }

} // Lunib