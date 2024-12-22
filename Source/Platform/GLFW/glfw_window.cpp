#include "glfw_window.h"
#include "Lunib/Core/engine.h"
#include "Platform/OpenGL/opengl_context.h"
#include "Lunib/Events/key_event.h"
#include "Lunib/Events/mouse_event.h"
#include "Lunib/Events/window_event.h"

// std
#include <iostream>

// Lib
#include <GLFW/glfw3.h>



namespace Lunib
{
	static int CursorModeToGLFWCursorMode(CursorMode p_mode)
	{
		switch (p_mode)
		{
			case Lunib::CursorMode::Hidden:   return GLFW_CURSOR_HIDDEN;
			case Lunib::CursorMode::Disabled: return GLFW_CURSOR_DISABLED;
			case Lunib::CursorMode::Normal:   return GLFW_CURSOR_NORMAL;
			default:
				return 0;
		}
	}

	static uint8_t s_GLFWWindowCount = 0;

	static void GLFWErrorCallback(int p_error, const char* p_description)
	{
		std::cout << "GLFW Error " << p_error << " :" << p_description << "\n";
	}

	GLFWWindow::GLFWWindow(const WindowSpecification &p_spec)
	{
		m_InitialWidth	= p_spec.Width;
		m_InitialHeight = p_spec.Height;

		Init(p_spec);
	}

	GLFWWindow::~GLFWWindow()
	{
		glfwDestroyWindow(m_Window);
		--s_GLFWWindowCount;

		if (s_GLFWWindowCount == 0)
		{
			glfwTerminate();
		}
	}

	#define SET_EVENT(event) 			\
	if (data.EventCallback)				\
		data.EventCallback(event);		\
	if (data.EventCallbackStd)			\
		data.EventCallbackStd(event);

	void GLFWWindow::Init(const WindowSpecification &p_spec)
	{
		m_Data.Title 				= p_spec.Title;
		m_Data.Width 				= p_spec.Width;
		m_Data.Height 				= p_spec.Height;
		m_Data.Vsync 				= p_spec.Vsync;
		m_Data.Mode 				= p_spec.Mode;

		if (s_GLFWWindowCount == 0)
		{
			if (!glfwInit())
			{
				throw std::runtime_error("Failed on glfwInit!");
			}
			glfwSetErrorCallback(GLFWErrorCallback);
		}

		{
			int width  				= int(p_spec.Width);
			int height 				= int(p_spec.Height);
			GLFWmonitor* monitor 	= nullptr;

			if (m_Data.Mode == WindowMode::Fullscreen)
				monitor 			= glfwGetPrimaryMonitor();

			glfwWindowHint(GLFW_DECORATED, m_Data.Mode != WindowMode::Borderless);

			if (p_spec.Maximize || m_Data.Mode == WindowMode::Borderless)
			{
				auto mode 			= glfwGetVideoMode(monitor ? monitor : glfwGetPrimaryMonitor());
				width  				= mode->width;
				height 				= mode->height;
			}

			if (m_Data.Mode == WindowMode::Windowed)
				glfwWindowHint(GLFW_MAXIMIZED, p_spec.Maximize);

		#if defined(LUNIB_DEBUG)
			if (Engine::GetAPI() == RenderAPI::OpenGL)
				glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
		#endif

			if (Engine::GetAPI() == RenderAPI::OpenGL)
			{
				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
				glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			#if defined(LUNIB_APPLE)
				glfwWindowHint(GLFW_SAMPLES, 1);
				glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
				glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_FALSE);
				glfwWindowHint(GLFW_COCOA_GRAPHICS_SWITCHING, GL_TRUE);
				glfwWindowHint(GLFW_STENCIL_BITS, 8); // Fixes 16 bit stencil bits in macOS.
				glfwWindowHint(GLFW_STEREO, GLFW_FALSE);
				glfwWindowHint(GLFW_SRGB_CAPABLE, GLFW_TRUE);
			#endif
			}

			glfwWindowHint(GLFW_RESIZABLE, p_spec.Resizable);

			m_Window 				= glfwCreateWindow(width, height, m_Data.Title.c_str(), monitor, m_OldWindow);

			if (m_OldWindow)
			{
				glfwDestroyWindow(m_OldWindow);
				m_OldWindow 		= nullptr;
			}
			else
				s_GLFWWindowCount++;
		}

		if (Engine::GetAPI() == RenderAPI::OpenGL)
		{
			glfwMakeContextCurrent(m_Window);
			m_Context = new OpenGLContext(glfwGetProcAddress);
		}

		{
			m_Resolutions.clear();
			GLFWmonitor* monitor 			= glfwGetPrimaryMonitor();
			if (monitor)
			{
				int count = 0;
				const GLFWvidmode* modes 	= glfwGetVideoModes(monitor, &count);

				for (int i = 0; i < count; i++)
				{
					Resolution res 			= {};
					res.Width 				= modes[i].width;
					res.Height 				= modes[i].height;
					res.RefreshRate 		= modes[i].refreshRate;
					m_Resolutions.push_back(res);
				}
			}
		}

		glfwSetWindowUserPointer(m_Window, &m_Data);

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* p_window, int p_width, int p_height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(p_window);
			data.Width = p_width;
			data.Height = p_height;

			WindowResizeEvent event(p_width, p_height);
			SET_EVENT(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* p_window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(p_window);
			WindowCloseEvent event;
			SET_EVENT(event);
		});

		glfwSetWindowFocusCallback(m_Window, [](GLFWwindow* p_window, int p_focused) 
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(p_window);
			if (p_focused)
			{
				WindowFocusEvent event;
				SET_EVENT(event);
			}
			else
			{
				WindowLostFocusEvent event;
				SET_EVENT(event);
			}
		});

		glfwSetWindowPosCallback(m_Window, [](GLFWwindow* p_window, int p_xpos, int p_ypos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(p_window);
			WindowMovedEvent event(p_xpos, p_ypos);
			SET_EVENT(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* p_window, int p_key, int p_scancode, int p_action, int p_mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(p_window);

			switch (p_action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(p_key, 0);
					SET_EVENT(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(p_key);
					SET_EVENT(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(p_key, true);
					SET_EVENT(event);
					break;
				}
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* p_window, unsigned int p_keycode)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(p_window);

			KeyTypedEvent event(p_keycode);
			SET_EVENT(event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* p_window, int p_button, int p_action, int p_mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(p_window);

			switch (p_action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(p_button);
					SET_EVENT(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(p_button);
					SET_EVENT(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* p_window, double p_xoffset, double p_yoffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(p_window);

			MouseScrolledEvent event((float)p_xoffset, (float)p_yoffset);
			SET_EVENT(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* p_window, double p_x, double p_y)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(p_window);

			MouseMovedEvent event((float)p_x, (float)p_y);
			SET_EVENT(event);
		});
	}

	void GLFWWindow::OnUpdate()
	{
		glfwPollEvents();
		if (Engine::GetAPI() == RenderAPI::OpenGL)
			glfwSwapBuffers(m_Window);
	}

	void GLFWWindow::Maximize()
	{
		if (m_Data.Mode == WindowMode::Windowed)
			glfwMaximizeWindow(m_Window);
	}

	void GLFWWindow::EnableVsync(bool p_enable)
	{
		m_Data.Vsync = p_enable;

		if (Engine::GetAPI() == RenderAPI::OpenGL)
			glfwSwapInterval(p_enable ? 1 : 0);
	}

	void GLFWWindow::SetCursorMode(CursorMode p_mode)
	{
		int mode = CursorModeToGLFWCursorMode(p_mode);
		if (mode != 0)
			glfwSetInputMode(m_Window, GLFW_CURSOR, mode);
	}

	void GLFWWindow::SetWindowMode(WindowMode p_mode, bool p_maximize /* = true */, bool p_resizable /* = true */)
	{
		WindowSpecification spec 	= {};
		spec.Width 					= m_InitialWidth;
		spec.Height 				= m_InitialHeight;
		spec.Mode 					= p_mode;
		spec.Title 					= m_Data.Title;
		spec.Maximize 				= p_maximize;
		spec.Resizable 				= p_resizable;

		m_OldWindow 				= m_Window;

		Init(spec);
	}

	void GLFWWindow::SetTitle(const std::string &p_title)
	{
		if (p_title == m_Data.Title)
			return;

		m_Data.Title 	= p_title;
		glfwSetWindowTitle(m_Window, m_Data.Title.c_str());
	}

	void GLFWWindow::SetPosition(const IVec2& p_pos)
	{
		if (p_pos == m_Data.Position)
			return;

		m_Data.Position = p_pos;
		glfwSetWindowPos(m_Window, p_pos.x, p_pos.y);
	}

	void GLFWWindow::SetWindowSize(uint32_t p_width, uint32_t p_height)
	{
		if (m_Data.Width == p_width && m_Data.Height == p_height)
			return;

		m_Data.Width 	= p_width;
		m_Data.Height 	= p_height;
		glfwSetWindowSize(m_Window, int(p_width), int(p_height));
	}

} // Lunib