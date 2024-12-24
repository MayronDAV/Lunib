#pragma once
#include "Lunib/Core/window.h"

#include "Lunib/Renderer/graphics_context.h"



struct GLFWwindow;

namespace Lunib
{
	class GLFWWindow : public Window
	{
		public:
			GLFWWindow(const WindowSpecification& p_spec);
			~GLFWWindow() override;

			void OnUpdate() override;

			void Maximize() override;

			void SetEventCallback(EventCallbackFn p_callback) override { m_Data.EventCallback = p_callback; }
			void SetEventCallback(EventCallbackFnStd p_callback) override { m_Data.EventCallbackStd = p_callback; }
			void EnableVsync(bool p_enable) override;
			void SetCursorMode(CursorMode p_mode) override;
			void SetWindowMode(WindowMode p_mode, bool p_maximize = true, bool p_resizable = true) override;
			void SetTitle(const std::string& p_title) override;
			void SetPosition(const IVec2& p_pos) override;
			void SetWindowSize(uint32_t p_width, uint32_t p_height) override;

			const std::vector<Resolution>& GetResolutions() override { return m_Resolutions; }
			bool IsVsync() const override { return m_Data.Vsync; }
			uint32_t GetWidth() const override;
			uint32_t GetHeight() const override;
			std::string GetTitle() const override { return m_Data.Title; }
			void* GetNativeWindow() const override { return m_Window; }
			IVec2 GetPos() const override { return m_Data.Position; }
			GraphicsContext& GetContext() { return *m_Context; }
			WindowMode GetMode() const override { return m_Data.Mode; }

		private:
			void Init(const WindowSpecification& p_spec);

		private:
			GLFWwindow* m_Window    	= nullptr;
			GLFWwindow* m_OldWindow 	= nullptr;
			GraphicsContext* m_Context 	= nullptr;

			uint32_t m_InitialWidth;
			uint32_t m_InitialHeight;

			struct WindowData
			{
				std::string Title;
				uint32_t Width;
				uint32_t Height;
				bool Vsync;
				WindowMode Mode;
				IVec2 Position;

				EventCallbackFn EventCallback 		= nullptr;
				EventCallbackFnStd EventCallbackStd = nullptr;
			};
			WindowData m_Data;

			std::vector<Resolution> m_Resolutions;
	};


} // Lunib