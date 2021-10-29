#pragma once
#include"Hazel/Layer/Layer.h"
#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Events/ApplicationEvent.h"
namespace Hazel
{
	class HAZEL_API ImGuiLayer:public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();
		void OnUpdate(); 
		void OnEvent(Event& event);
		void OnAttach();
		void OnDetach();

	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMoveEvent(MouseMoveEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		
		bool OnKeyPressedEvent(KeyPressEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);


	private:
		float m_time = 0.0f;
	};


}