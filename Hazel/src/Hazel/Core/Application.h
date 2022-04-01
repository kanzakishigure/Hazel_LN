#pragma once
#include "Hazel/Core/Core.h"
#include "Hazel/Events/Event.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Core/LayerStack.h"
#include "Window.h"
#include "Hazel//ImGui/ImGuiLayer.h"
#include "Hazel/Core/TimeStep.h"
namespace Hazel{


	class HAZEL_API Application
	{
		public:
			Application();

			//��֤application�����������ʱ���ܵ��õ������������������
			virtual ~Application();

			void run();
			void OnEvent(Event& e);
			void PushLayer(Layer* layer);
			void PushOverlay(Layer* overlay);
			void Close() { m_Running = false; }
			//���ص���application�ĵ��������Բ�Ӧ�ý�ָ�뷵��
			inline static Application& Get() { return *s_Instance; }
			inline  Window& GetWindow() { return *m_Window; }
	public:
		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running =true;
		bool m_Minimized = false;

		LayerStack m_LayerStack;
		static Application* s_Instance;
		TimeStep m_TimeStep;
		float m_LastFrameTime=0.0f;
	private:
		
	};

	Application* createApplication();//�ú���ֻӦ��Ӧ�ö�ʵ��


}

