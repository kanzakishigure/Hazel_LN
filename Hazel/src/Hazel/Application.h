#pragma once
#include"Core/Core.h"
#include"Events/Event.h"
#include"Hazel/Events/ApplicationEvent.h"
#include"Layer/LayerStack.h"
#include"Window.h"
namespace Hazel{


	class HAZEL_API Application
	{
		public:
			Application();
			virtual ~Application();//�������sandbox���γ����࣬�����麯���������ڼ̳е������ڽ���ʵ��

			void run();
			void OnEvent(Event& e);
			void PushLayer(Layer* layer);
			void PushOverlay(Layer* overlay);
			//���ص���application�ĵ��������Բ�Ӧ�ý�ָ�뷵��
			inline static Application& Get() { return *s_Instance; }
			inline  Window& GetWindow() { return *m_Window; }
			//void* getthisPoint() { return this; }
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running =true;
		bool OnWindowClose(WindowCloseEvent& e);
		LayerStack m_LayerStack;
		static Application* s_Instance;
	};

	Application* createApplication();//�ú���ֻӦ��Ӧ�ö�ʵ��


}

