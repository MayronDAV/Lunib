#pragma once
#include "Lunib/Core/base.h"

// std
#include <string>
#include <sstream>
#include <functional>



namespace Lunib
{
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved, WindowDrop,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		EventNone                   = 0,
		EventCategoryWindow    		= BIT(0),
		EventCategoryInput          = BIT(1),
		EventCategoryKeyboard       = BIT(2),
		EventCategoryMouse          = BIT(3),
		EventCategoryMouseButton    = BIT(4)
	};

	#define EVENT_CLASS_METHODS(type)                                                   \
			static EventType GetStaticType() { return EventType::type; }                \
			virtual EventType GetEventType() const override { return GetStaticType(); } \
			virtual const char* GetName() const override { return #type; }

	#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class LUNIB_API Event
	{
		public:
			template<typename T>
			using EventFn = bool (*)(T&);

			template<typename T>
			using EventFnStd = std::function<bool(T&)>;

		public:
			virtual ~Event() 						= default;

			bool Handled 							= false;

			virtual EventType GetEventType() const	{ return EventType::None;	}
			virtual const char* GetName() const		{ return "EventNone";		}
			virtual int GetCategoryFlags() const	{ return EventNone;			}
			virtual std::string ToString() const 	{ return GetName();			}

			inline bool IsInCategory(EventCategory p_category) const
			{
				return GetCategoryFlags() & p_category;
			}

			template<typename T>
			inline bool Dispatch(EventFn<T> p_func)
			{
				if (GetEventType() == T::GetStaticType())
				{
					Handled = p_func(static_cast<T&>(*this));
					return true;
				}
				return false;
			}

			template<typename T>
			inline bool Dispatch(EventFnStd<T> p_func)
			{
				if (GetEventType() == T::GetStaticType())
				{
					Handled = p_func(static_cast<T&>(*this));
					return true;
				}
				return false;
			}

			inline operator std::string() const
			{
				return ToString();
			}

			inline bool operator==(const EventType& p_type) const
			{
				return GetEventType() == p_type;
			}

			friend std::ostream& operator<<(std::ostream& p_os, const Event& p_event)
			{
				p_os << p_event.ToString();
				return p_os;
    		}
	};

};