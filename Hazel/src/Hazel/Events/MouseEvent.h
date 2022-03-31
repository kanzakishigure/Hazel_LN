#pragma once
#include"Hazel/Events/Event.h"
#include"Hazel/Core/MouseCodes.h"

namespace Hazel
{
	class HAZEL_API MouseMoveEvent :public Event
	{
	public:
		MouseMoveEvent(const float x,const float y)
			:m_MouseX(x),m_MouseY(y){}
		float GetX() { return m_MouseX; }
		float GetY() { return m_MouseY; }

		std::string ToString() const override 
		{ 
			std::stringstream ss;
			ss << "MouseMoveEvent:" << "X:"<<m_MouseX <<","<<"Y:"<< m_MouseY;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryInput|EventCategoryMouse)
	private:
		float m_MouseX;
		float m_MouseY;


	};
	class HAZEL_API MouseScrolledEvent:public Event
	{
	public:
		MouseScrolledEvent(const float xoffset,const float yoffset)
			:m_Xoffset(xoffset),m_Yoffset(yoffset){}

		float GetXOffset() const { return m_Xoffset; }
		float GetYOffset() const { return m_Yoffset; }
		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
	private:
		float m_Xoffset, m_Yoffset;
	};

	class HAZEL_API MouseButtonEvent :public Event
	{
	public:
		MouseCode GetMouseButton()const { return m_Button; }
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse| EventCategoryMouseButton)
	protected:
		MouseButtonEvent(const MouseCode button)
			:m_Button(button) {}
		MouseCode m_Button;
	};

	class HAZEL_API MouseButtonPressedEvent:public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(const MouseCode button)
			:MouseButtonEvent(button){}

		std::string ToString ()const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonPressed)
	};
	class HAZEL_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(const MouseCode button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

}