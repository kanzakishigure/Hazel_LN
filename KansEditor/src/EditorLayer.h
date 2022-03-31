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
		glm::vec2 m_ViewportSize = glm::vec2(0.0f,0.0f);
		Ref<Texture2D> ChessTexture;
		Ref<Texture2D> LightPop;
		Ref<Texture2D>TextureSheet;
		Ref<Texture2D> HuTao;

		Ref<SubTexture2D> B_Rockstairs[2];
		Ref<SubTexture2D> W_Rockstairs[2];
		Ref<SubTexture2D> grassland[3];
		Ref<SubTexture2D> Y_roof[6];
		Ref<SubTexture2D> B_roof[6];
		//Hazel::Ref<Hazel::FrameBuffer> m_Framebuffer;

		//临时成员，用来进行2drenderer的进一步抽象
		glm::vec4 FlatColor = { 1.0,1.0,1.0,1.0 };
		ParticleSystem m_ParticleSys;
		ParticleProps m_Particle;

		Ref<FrameBuffer> m_Framebuffer;
	};


}
