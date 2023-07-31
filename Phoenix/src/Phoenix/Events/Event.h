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

	enum class EventType //�о��˲�ͬ���¼�����
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory //�������¼��ķ���
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
	//���������¼����͵ĺ�

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }
	//���������¼�����ĺ�

	class Event
	{
	public:
		virtual ~Event() = default;

		bool m_Handled = false;

		virtual EventType GetEventType() const = 0;//Ŀ������ÿ�������෵���Լ��ض����¼����ͣ��Ա����¼��ַ�ʱ�������ͼ���ƥ�䡣
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		/*ʹ�� virtual �ؼ��ֽ���������Ϊ�麯��������ʵ������ʱ��̬�ԡ�
		����ζ��������ʱ�����ݶ����ʵ�����ͣ���������Ӧ������������д�ĺ�����
		ͨ���ڻ����������麯��������Ϊ�����̳в�νṹ�ṩͳһ�Ľӿڣ�ͬʱ�����������������������ṩ�Զ����ʵ�֡�*/

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
	//�����¼�������

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
	//��־��¼
}