#pragma once
#include "Hazel/Renderer/Camera.h"
namespace Hazel {


	class SceneCamera:public Camera {


	public: 
		enum class ProjectionType{ Perspective = 0,Orthographic };
	public:
		//设置相机属性
		void SetPerspectve(float PerspectiveFOV, float Near, float Far);
		void SetOrthographic(float Size, float Near, float Far);
		void SetViewportSize(uint32_t width, uint32_t height);
		//设置透视摄像机参数
		void SetPerspectiveVerticalFOV(float VerticalFOV) { m_PerspectiveFOV = glm::radians(VerticalFOV); }
		float GetPerspectiveVerticalFOV() const { return glm::degrees(m_PerspectiveFOV); }
		void SetPerspectiveNearClip(float NearClip) { m_PerspectiveNear = NearClip; }
		float GetPerspectiveNearClip() const { return m_PerspectiveNear; }
		void SetPerspectiveFarClip(float FarClip) { m_PerspectiveFar = FarClip; }
		float GetPerspectiveFarClip() const { return m_PerspectiveFar; }
		//设置正交摄像机参数
		void SetOrthographicSize(float size) { m_OrthographicSize = size; }
		float GetOrthographicSize() const { return m_OrthographicSize; }
		void SetOrthographicNearClip(float nearClip) { m_OrthographicNear = nearClip; }
		float GetOrthographicNearClip() const { return m_OrthographicNear; }
		void SetOrthographicFarClip(float farClip) { m_OrthographicFar = farClip; }
		float GetOrthographicFarClip() const { return m_OrthographicFar; }

		void SetProjectionTypr(ProjectionType Type) { m_ProjectionType = Type; }
		ProjectionType GetProjectionType() { return m_ProjectionType; }

	private:
		//now did't support persipective
		ProjectionType m_ProjectionType = ProjectionType::Orthographic;
		
		float m_PerspectiveFOV = glm::radians(45.0f);;
		float m_PerspectiveFar=1000.0f; float m_PerspectiveNear=0.1f;

		float m_OrthographicSize = 10.0f;
		float m_OrthographicFar = 1.0f; float m_OrthographicNear = -1.0f;

	};
}