#pragma once

#include "Phoenix/core.h" 
#include <sstream>
#include <string>

namespace Phoenix
{

	//
	//
	//
	//

	enum class EventType //列举了不同的事件类型
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory //定义了事件的分类
	{
		None = 0,
		EventCategoryApplication  = BIT(0),
		EventCategoryInput        = BIT(1),
		EventCategoryKeyboard     = BIT(2),
		EventCategoryMouse        = BIT(3),
		EventCategoryMouseButton  = BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
							    virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }
	//用于声明事件类型的宏

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }
	//用于声明事件分类的宏

	class Event
	{
	public:
		virtual ~Event() = default;

		bool m_Handled = false;

		virtual EventType GetEventType() const = 0;//目的是让每个派生类返回自己特定的事件类型，以便在事件分发时进行类型检查和匹配。
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		/*使用 virtual 关键字将函数声明为虚函数，可以实现运行时多态性。
		这意味着在运行时，根据对象的实际类型，将调用相应的派生类中重写的函数。
		通过在基类中声明虚函数，可以为整个继承层次结构提供统一的接口，同时允许派生类根据自身的特性提供自定义的实现。*/

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
		
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		// F will be deduced by the compiler
		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled |= func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};
	//创建事件调度器

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
	//日志记录
}