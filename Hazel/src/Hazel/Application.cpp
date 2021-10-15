#include"hzpch.h"
#include "Application.h"

#include"Hazel/Events/ApplicationEvent.h"
#include"Hazel/Log.h"
namespace Hazel
{

	void Application::run()
	{
		WindowResizeEvent e(1920, 1080);
		HZ_TRACE(e);
		while (m_Running)
		{
			m_Window->OnUpdate();
		}
	}
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Running = true;
	}
	Application::~Application()
	{

	}

}
