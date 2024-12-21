#pragma once

#include "event.h"

#include "Lunib/Math/Ext/vector.h"



namespace Lunib
{
	class LUNIB_API MouseMovedEvent : public Event
	{
		public:
			MouseMovedEvent(float p_x, float p_y)
				: m_MouseX(p_x), m_MouseY(p_y) {}

			inline float GetX() const { return m_MouseX; }
			inline float GetY() const { return m_MouseY; }
			inline Vec2 GetPos() const { return Vec2(m_MouseX, m_MouseY); }

			std::string ToString() const override
			{
				std::stringstream ss;
				ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
				return ss.str();
			}

			EVENT_CLASS_METHODS(MouseMoved)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

		private:
			float m_MouseX;
			float m_MouseY;
	};

	class LUNIB_API MouseScrolledEvent : public Event
	{
		public:
			MouseScrolledEvent(float p_xoffset, float p_yoffset)
				: m_XOffset(p_xoffset), m_YOffset(p_yoffset) {}

			inline float GetXOffset() const { return m_XOffset; }
			inline float GetYOffset() const { return m_YOffset; }
			inline Vec2 GetOffset() const { return Vec2(m_XOffset, m_YOffset); }

			std::string ToString() const override
			{
				std::stringstream ss;
				ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
				return ss.str();
			}

			EVENT_CLASS_METHODS(MouseScrolled)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

		private:
			float m_XOffset;
			float m_YOffset;
	};

	class LUNIB_API MouseButtonEvent : public Event
	{
		public:
			inline int GetMouseButton() const { return m_Button; }

			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

		protected:
			explicit MouseButtonEvent(int p_button)
				: m_Button(p_button) {}

			int m_Button;
	};

	class LUNIB_API MouseButtonPressedEvent : public MouseButtonEvent
	{
		public:
			explicit MouseButtonPressedEvent(int p_button)
				: MouseButtonEvent(p_button) {}

			std::string ToString() const override
			{
				std::stringstream ss;
				ss << "MouseButtonPressedEvent: " << m_Button;
				return ss.str();
			}

			EVENT_CLASS_METHODS(MouseButtonPressed)
	};

	class LUNIB_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
		public:
			explicit MouseButtonReleasedEvent(int p_button)
				: MouseButtonEvent(p_button) {}

			std::string ToString() const override
			{
				std::stringstream ss;
				ss << "MouseButtonReleasedEvent: " << m_Button;
				return ss.str();
			}

			EVENT_CLASS_METHODS(MouseButtonReleased)
	};

}