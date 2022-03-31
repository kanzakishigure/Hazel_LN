#pragma once
#include "Hazel/Renderer/OrthographicCamera.h"
#include "Hazel/Core/TimeStep.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Events/Event.h"
#include "Hazel/Core/Core.h"

namespace Hazel {
	class OrthographicCameraController 
	{
	public:
		OrthographicCameraController(float aspecRatio,bool Rotation = false);
		void OnUpdate(TimeStep ts);
		void OnEvent(Event& e);

		void OnResize(uint32_t width, uint32_t height);
		
		const OrthographicCamera& GetOrthographicCamera() const  { return m_Camera; }
		OrthographicCamera& GetOrthographicCamera() { return m_Camera; }
		const OrthographicCameraBounds& GetBounds() const { return m_Bounds; }
		OrthographicCameraBounds& GetBounds() { return m_Bounds; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		float m_AspecRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCameraBounds m_Bounds;
		OrthographicCamera m_Camera;
		
		bool m_Rotation;
		
		glm::vec3 m_CameraPos = {0.0f,0.0f,0.0f};
		float m_CameraRotation = 0.0f;
		float m_CameraTranslationSpeed = 1.0f;
		float m_CameraRotationSpeed = 1.0f;



	};
}