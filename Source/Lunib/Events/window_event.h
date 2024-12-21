#pragma once

#include "event.h"
#include "Lunib/Math/Ext/vector.h"

// std
#include <vector>


namespace Lunib
{
	class LUNIB_API WindowResizeEvent : public Event
	{
		public:
			WindowResizeEvent(uint32_t p_width, uint32_t p_height)
				: m_Width(p_width), m_Height(p_height) {}

			inline uint32_t GetWidth() const { return m_Width; }
			inline uint32_t GetHeight() const { return m_Height; }

			std::string ToString() const override
			{
				std::stringstream ss;
				ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
				return ss.str();
			}

			EVENT_CLASS_METHODS(WindowResize)
			EVENT_CLASS_CATEGORY(EventCategoryWindow)

		private:
			uint32_t m_Width;
			uint32_t m_Height;
	};

	class LUNIB_API WindowCloseEvent : public Event
	{
		public:
			WindowCloseEvent() = default;

			EVENT_CLASS_METHODS(WindowClose)
			EVENT_CLASS_CATEGORY(EventCategoryWindow)
	};

	class LUNIB_API WindowFocusEvent : public Event
	{
		public:
			WindowFocusEvent() = default;

			EVENT_CLASS_METHODS(WindowFocus)
			EVENT_CLASS_CATEGORY(EventCategoryWindow)
	};

	class LUNIB_API WindowLostFocusEvent : public Event
	{
		public:
			WindowLostFocusEvent() = default;

			EVENT_CLASS_METHODS(WindowLostFocus)
			EVENT_CLASS_CATEGORY(EventCategoryWindow)
	};

	class LUNIB_API WindowMovedEvent : public Event
	{
		public:
			WindowMovedEvent(int p_x, int p_y) : m_PosX(p_x), m_PosY(p_y) {}

			int GetX() const { return m_PosX; }
			int GetY() const { return m_PosY; }
			IVec2 GetPos() const { return IVec2(m_PosX, m_PosY); }

			std::string ToString() const override
			{
				std::stringstream ss;
				ss << "WindowMovedEvent: " << m_PosX << ", " << m_PosY;
				return ss.str();
			}

			EVENT_CLASS_METHODS(WindowMoved)
			EVENT_CLASS_CATEGORY(EventCategoryWindow)

		private:
			int m_PosX;
			int m_PosY;
	};

	class LUNIB_API WindowDropEvent : public Event
	{
		public:
			explicit WindowDropEvent(const std::vector<std::string>& p_paths)
				: m_Paths(p_paths) {}

			explicit WindowDropEvent(std::vector<std::string>&& p_paths)
				: m_Paths(std::move(p_paths)) {}

			const std::vector<std::string>& GetPaths() const { return m_Paths; }

			EVENT_CLASS_METHODS(WindowDrop)
			EVENT_CLASS_CATEGORY(EventCategoryWindow)

		private:
			std::vector<std::string> m_Paths;
	};
}
