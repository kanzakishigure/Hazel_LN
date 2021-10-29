#pragma once
#include"Hazel/Events/Event.h"
#include<sstream>
namespace Hazel{
	
	class HAZEL_API WindowResizeEvent: public Event
	{
	public:
		WindowResizeEvent (unsigned int Width, unsigned int Hight)
			: m_Width(Width), m_Hight(Hight) {};
		 
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent:" << m_Width <<","<< m_Hight ;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

		unsigned int GetWindth()const { return m_Width; }
		unsigned int GetHight()const { return m_Hight; }

	private:
		unsigned int m_Width, m_Hight;
	};
	class HAZEL_API WindowCloseEvent:public Event
	{
	public:
		WindowCloseEvent()=default;
		 
		EVENT_CLASS_TYPE(WindowsClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:

	};
	class HAZEL_API AppTickEvent : public Event
	{
	public:
		AppTickEvent ()=default;
		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:

	};
	class HAZEL_API AppUpdateEvent:public Event
	{
	public:
		AppUpdateEvent () = default;
		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:

	};
	class HAZEL_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() = default;

		EVENT_CLASS_TYPE(AppRender)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
	/*
	类中的宏可以等价替换为
	static EventType GetStaticType(){return  EventType::type;}
	virtual EventType GetEventType() const override { return GetStaticType();}
	virtual const char* GetName() const override {return #type;}
    */
}