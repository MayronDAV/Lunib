#pragma once

#include "event.h"



namespace Lunib 
{

	class LUNIB_API KeyEvent : public Event
	{
		public:
			inline int GetKeyCode() const { return m_KeyCode; }

			EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

		protected:
			explicit KeyEvent(int p_keycode)
				: m_KeyCode(p_keycode) {}

			int m_KeyCode;
	};

	class LUNIB_API KeyPressedEvent : public KeyEvent
	{
		public:
			KeyPressedEvent(int p_keycode, bool p_isRepeat = false)
				: KeyEvent(p_keycode), m_IsRepeat(p_isRepeat) {}

			bool IsRepeat() const { return m_IsRepeat; }

			std::string ToString() const override
			{
				std::stringstream ss;
				ss << "KeyPressedEvent: " << m_KeyCode << " (repeat = " << m_IsRepeat << ")";
				return ss.str();
			}

			EVENT_CLASS_METHODS(KeyPressed)

		private:
			bool m_IsRepeat;
	};

	class LUNIB_API KeyReleasedEvent : public KeyEvent
	{
		public:
			explicit KeyReleasedEvent(int p_keycode)
				: KeyEvent(p_keycode) {}

			std::string ToString() const override
			{
				std::stringstream ss;
				ss << "KeyReleasedEvent: " << m_KeyCode;
				return ss.str();
			}

			EVENT_CLASS_METHODS(KeyReleased)
	};

	class LUNIB_API KeyTypedEvent : public KeyEvent
	{
		public:
			explicit KeyTypedEvent(int p_keycode)
				: KeyEvent(p_keycode) {}

			std::string ToString() const override
			{
				std::stringstream ss;
				ss << "KeyTypedEvent: " << m_KeyCode;
				return ss.str();
			}

			EVENT_CLASS_METHODS(KeyTyped)
	};
}
