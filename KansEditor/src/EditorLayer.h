#pragma once
#include <Hazel.h>

namespace Hazel {
	class EditorLayer :public Hazel::Layer
	{

	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(Hazel::TimeStep ts) override;
		void OnEvent(Hazel::Event& e) override;
		virtual void OnImGuiRender() override;
	private:
		ShaderLibrary shaderLibrary;
		OrthographicCameraController m_CameraController;
		
		Ref<FrameBuffer> m_Framebuffer;
		glm::vec2 m_ViewportSize = glm::vec2(0.0f,0.0f);

		bool m_ViewportFocused= false,m_viewprotHovered;
		
		Ref<Scene> m_ActiveScene;
		Entity squalEntity;
		glm::vec4 FlatColor = { 1.0,1.0,1.0,1.0 };
	};


}
