#include"hzpch.h"

#include "Application.h"
#include "Hazel/Core/Log.h"
#include "Input.h"
#include "Renderer/Renderer.h"
#include "Hazel/Core/KeyCodes.h"

#include <GLFW/glfw3.h>
namespace Hazel
{
	#define BIND_EVENT_FN(x) std::bind(&x,this,std::placeholders::_1)
	Application* Application::s_Instance = nullptr;
	//ʹ����bind��ʹ��thisָ������õĽ�����thisָ���Ϊ��һ������
	

	Application::Application()
	{
		HZ_CORE_ASSERT(!s_Instance,"Application already exist!");

		HZ_PROFILE_FUCTION();
		s_Instance = this;
		m_Window = Window::Create();
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		
	}
	Application::~Application()
	{
		
	}
	void Application::run()
	{
		HZ_PROFILE_FUCTION();
		while (m_Running)
		{
			float time = glfwGetTime();
			m_TimeStep = TimeStep(glfwGetTime()-m_LastFrameTime );
			m_LastFrameTime = time;

			
			if (!m_Minimized)
			{
				{
					HZ_PROFILE_SCOPE("application_layerstark_update");
					//��ͨlayer������Ⱦ
					for (Layer* layer : m_LayerStack)
					layer->OnUpdate(m_TimeStep);
				}
				{
					HZ_PROFILE_SCOPE("application_imgui_layerstark_update");
					//���� ImGuiLayer��Ⱦ
					m_ImGuiLayer->Begin();
					for (Layer* layer : m_LayerStack)
					layer->OnImGuiRender();
					m_ImGuiLayer->End();
				}
			}
			m_Window->OnUpdate();

		}
	}
	void Application::OnEvent(Event& e)
	{
		HZ_PROFILE_FUCTION();
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));

		for (auto it = m_LayerStack.begin() ;it!=m_LayerStack.end(); ++it)
		{
			
			(*it)->OnEvent(e);//ʱ��Ĵ���������Ⱦ��layer��ǰ��͸
			if (e.Handeled)
				break;
		}
	}
	void Application::PushLayer(Layer* layer)
	{
		HZ_PROFILE_FUCTION();

		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	void Application::PushOverlay(Layer* overlay)
	{
		HZ_PROFILE_FUCTION();

		m_LayerStack.PushLayer(overlay);
		overlay->OnAttach();
	}
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;

		return true;
	}
	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		HZ_PROFILE_FUCTION();

		if (e.GetHeight() == 0 || e.GetWidth() == 0)
		{
			m_Minimized = true;
			return false;
		}
		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		return false;
	}

}