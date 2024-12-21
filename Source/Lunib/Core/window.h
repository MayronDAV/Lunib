#pragma once
#include "base.h"
#include "definitions.h"
#include "Lunib/Events/event.h"
#include "Lunib/Math/Ext/vector.h"

// std
#include <string>
#include <vector>


namespace Lunib
{

	struct LUNIB_API Resolution
	{
		uint32_t Width;
		uint32_t Height;
		uint32_t RefreshRate;
	};

	struct LUNIB_API WindowSpecification
	{
		std::string Title   = "Sandbox";
		uint32_t Width      = 800;
		uint32_t Height     = 600;
		bool Vsync          = false;
		bool Maximize 		= true;
		bool Resizable 		= true;
		WindowMode Mode     = WindowMode::Windowed;
	};

	class LUNIB_API Window
	{
		public:
			using EventCallbackFn = void (*)(Event&);
			using EventCallbackFnStd = std::function<void(Event&)>;


		public:
			virtual ~Window() = default;

			virtual void OnUpdate() 											= 0;

			virtual void Maximize() 											= 0;

			virtual void SetEventCallback(EventCallbackFn p_callback) 			= 0;
			virtual void SetEventCallback(EventCallbackFnStd p_callback) 		= 0;
			virtual void SetWindowMode(WindowMode p_mode, bool p_maximize = true, bool p_resizable = true) = 0;
			virtual void EnableVsync(bool p_enable) 							= 0;
			virtual void SetCursorMode(CursorMode p_mode) 						= 0;
			virtual void SetTitle(const std::string& p_title) 					= 0;
			virtual void SetPosition(const IVec2& p_pos) 						= 0;
			virtual void SetWindowSize(uint32_t p_width, uint32_t p_height) 	= 0;

			virtual bool IsVsync() const 										= 0;
			virtual const std::vector<Resolution>& GetResolutions() 			= 0;
			virtual uint32_t GetWidth() const 									= 0;
			virtual uint32_t GetHeight() const 									= 0;
			virtual std::string GetTitle() const								= 0;
			virtual void* GetNativeWindow() const 								= 0;
			virtual IVec2 GetPos() const 										= 0;
			virtual WindowMode GetMode() const 									= 0;

			static Window* Create(const WindowSpecification& p_spec);
	};

} // Lunib