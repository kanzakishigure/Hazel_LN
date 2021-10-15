#pragma once

#include"Hazel/Events/Event.h"
#include"Hazel/Core/KeyCodes.h"
namespace Hazel {


	//KeyEvent的基类，用于后续KeyEvent的模板
	class HAZEL_API KeyEvent:public Event
	{
	public:
		KeyCode GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard|EventCategoryInput)

	protected:
		KeyEvent(const KeyCode keycode)
			:m_KeyCode(keycode){}
		KeyCode m_KeyCode;
	};
	class HAZEL_API KeyPressEvent :public KeyEvent
	{
	public:
		//子类通过调用父类构造函数，对从父类继承的值进行赋值
		KeyPressEvent(const KeyCode keycode, const uint16_t repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount){}

		uint16_t GetRepeatCount() const { return m_RepeatCount; }
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyPressed)
	private:
		uint16_t m_RepeatCount;
	};
	class HAZEL_API KeyReleasedEvent :public KeyEvent
	{
	public:
		KeyReleasedEvent(KeyCode keycode )
			:KeyEvent(keycode){}
		
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyReleased)
	};
	class HAZEL_API KeyTypedEvent:public KeyEvent
	{
	public:
		KeyTypedEvent(KeyCode keycode)
			:KeyEvent(keycode){}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyTyped)
		
	};




}