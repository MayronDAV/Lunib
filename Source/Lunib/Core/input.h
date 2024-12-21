#pragma once
#include "base.h"
#include "window.h"
#include "Lunib/Math/Ext/vector.h"


namespace Lunib
{
    class LUNIB_API Input
    {
        public:
            virtual ~Input() = default;
            
            virtual bool IsKeyPressed(int p_keycode) const                  = 0;
			virtual bool IsMouseButtonPressed(int p_button) const           = 0;

			bool IsKeyPressed(Event& p_event, int p_keyCode);
			bool IsMouseButtonPressed(Event& p_event, int p_button);

            virtual Vec2  GetMousePosition() const                          = 0;
			virtual float GetMouseX() const                                 = 0;
			virtual float GetMouseY() const                                 = 0;

            static Input* Create(Window* p_window);
    };

} // Lunib