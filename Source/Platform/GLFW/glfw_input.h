#pragma once
#include "Lunib/Core/input.h"


struct GLFWwindow;

namespace Lunib
{
	class GLFWInput : public Input
	{
		public:
			GLFWInput(Window* p_window);
			~GLFWInput() override = default;
			
			bool IsKeyPressed(int p_keycode) const override;
			bool IsMouseButtonPressed(int p_button) const override;

			Vec2  GetMousePosition() const override;
			float GetMouseX() const override;
			float GetMouseY() const override;

		private:
			GLFWwindow* m_Window = nullptr;
	};
	
} // Lunib
