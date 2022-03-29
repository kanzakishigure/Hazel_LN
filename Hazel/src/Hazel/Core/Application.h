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
			virtual ~Application();//该类会在sandbox内形成子类，固作虚函数。方便在继承的子类内进行实现

			void run();
			void OnEvent(Event& e);
			void PushLayer(Layer* layer);
			void PushOverlay(Layer* overlay);
			//返回的是application的单例，所以不应该将指针返回
			inline static Application& Get() { return *s_Instance; }
			inline  Window& GetWindow() { return *m_Window; }
			
			ImGuiLayer* m_ImGuiLayer;
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		Scope<Window> m_Window;
		bool m_Running =true;
		bool m_Minimized = false;

		LayerStack m_LayerStack;
		static Application* s_Instance;
		TimeStep m_TimeStep;
		float m_LastFrameTime=0.0f;
	private:
		
	};

	Application* createApplication();//该函数只应在应用端实现


}

