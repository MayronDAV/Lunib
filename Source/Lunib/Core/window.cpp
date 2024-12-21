#include "window.h"

#include "Platform/GLFW/glfw_window.h"

namespace Lunib
{
	Window* Window::Create(const WindowSpecification& p_spec)
	{
		return new GLFWWindow(p_spec);
	}


} // Lunib