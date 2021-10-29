#include"hzpch.h"

#include "Application.h"
#include"Hazel/Log.h"
#include "Input.h"

#include "glm/glm.hpp"
#include<glad/glad.h>
namespace Hazel
{
	#define BIND_EVENT_FN(x) std::bind(&x,this,std::placeholders::_1)
	Application* Application::s_Instance = nullptr;
	//使用在bind中使用this指针会永久的将函数this指针绑定为第一个参数


	Application::Application()
	{
		HZ_CORE_ASSERT(!s_Instance,"Application already exist!");

		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
	}
	Application::~Application()
	{

	}
	void Application::run()
	{

		while (m_Running)
		{
			glClearColor(0.54f, 0.63f, 0.6588f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			//auto [x, y] = Input::GetMousePosition();
			//HZ_CORE_TRACE("Input_Log:x:{0}y:{1}", x, y);
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();
			
			m_Window->OnUpdate();

		}
	}
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		for (auto it = m_LayerStack.end() ;it!=m_LayerStack.begin();)
		{
			((Layer*)*(--it))->OnEvent(e);//时间的处理从最后渲染的layer向前穿透
			if (e.Handeled)
				break;
		}
	}
	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushLayer(overlay);
		overlay->OnAttach();
	}
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;

		return true;
	}
}