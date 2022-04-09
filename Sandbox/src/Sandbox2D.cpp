#include "Sandbox2D.h"
#include <imgui.h>
#include "Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const int S_mapwidth = 24;
static const char* S_mapTiles= "";
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Sandbox2DLayer::Sandbox2DLayer()
	:m_CameraController(1920.0f / 1080.0f), Layer("sandbox2D")
{
	
}


void Sandbox2DLayer::OnAttach()
{
	HZ_PROFILE_FUCTION();
	ChessTexture = Hazel::Texture2D::Create("assets/textures/Checkerboard.png");
	LightPop = Hazel::Texture2D::Create("assets/textures/lightpop_L.png");
	TextureSheet = Hazel::Texture2D::Create("assets/textures/RPGpack_sheet_2X.png");
	HuTao = Hazel::Texture2D::Create("assets/textures/hutao.png");
	W_Rockstairs[0] = Hazel::SubTexture2D::CreateFromCroods(TextureSheet, { 16,5 }, { 128,128 });
	W_Rockstairs[1] = Hazel::SubTexture2D::CreateFromCroods(TextureSheet, { 17,5 }, { 128,128 });
	B_Rockstairs[0] = Hazel::SubTexture2D::CreateFromCroods(TextureSheet, { 7,5 }, { 128,128 });
	B_Rockstairs[1] = Hazel::SubTexture2D::CreateFromCroods(TextureSheet, { 8,5 }, { 128,128 });
	Y_roof[0] = Hazel::SubTexture2D::CreateFromCroods(TextureSheet, { 0,4 }, { 128,128 }, { 2,3 });

	Hazel::FrameBufferSpecification spec;
	spec.Width = Hazel::Application::Get().GetWindow().GetWidth();
	spec.Height = Hazel::Application::Get().GetWindow().GetHeight();
	m_Framebuffer = Hazel::FrameBuffer::Create(spec);
	

	m_Particle.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
	m_Particle.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	m_Particle.SizeBegin =0.5f, m_Particle.SizeVariation = 0.3f, m_Particle.SizeEnd = 0.0f;
	m_Particle.LifeTime = 1.5f;
	m_Particle.Velocity = { 0.0f, 0.0f };
	m_Particle.VelocityVariation = { 6.0f, 2.0f };
	m_Particle.Position = { 0.0f, 0.0f };
}

void Sandbox2DLayer::OnDetach()
{
	HZ_PROFILE_FUCTION();
	HZ_CORE_INFO("call detach");
	Hazel::Renderer2D::Shutdown();
	
}

void Sandbox2DLayer::OnUpdate(Hazel::TimeStep ts)
{
	HZ_PROFILE_FUCTION();
	//update
	{
		m_CameraController.OnUpdate(ts);

	}
	Hazel::Renderer2D::ResetStats();
	//rendererprep
	{
		//HazelTools::InstrumentationTimer timer();
		Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Hazel::RenderCommand::Clear();
		

	}
	//rendering
	{
		static float stride = 0;
		stride += ts ;
		HZ_PROFILE_SCOPE("rendering");
		Hazel::Renderer2D::BeginScene(m_CameraController.GetOrthographicCamera());


		//transfrom Test
#if 0
		Hazel::Renderer2D::DrawQuad({ 1.0f,1.0f }, { 2.0f,2.0f }, glm::vec4(153.0f / 256, 90.0f / 256, 102.0f / 256, 1.0f));
		Hazel::Renderer2D::DrawQuad({ -1.0f,-1.0f }, { 2.0f,2.0f }, glm::vec4(103.0f / 256, 120.0f / 256, 102.0f / 256, 1.0f));
		Hazel::Renderer2D::DrawRotateQuad({ 0.0f,0.0f },stride ,{ 4.0f,4.0f },glm::vec4(130.0f / 256, 160.0f / 256, 30.0f / 256, 1.0f));
		
		Hazel::Renderer2D::DrawQuad({ 0.0f, 0.0f,-0.1f },{ 10.0f,10.0f }, FlatColor);
		

		Hazel::Renderer2D::DrawQuad({ 0.0f,0.0f,0.0f }, { 8.0f,4.5f }, LightPop);
#endif


		// texturesheet TEST
#if 1
		Hazel::Renderer2D::DrawQuad({ 0.0f,0.0f }, { 2.0f,3.0f }, Y_roof[0]);
		Hazel::Renderer2D::DrawQuad({ 0.0f,2.0f }, { 1.0F,1.0F }, W_Rockstairs[0]);
		Hazel::Renderer2D::DrawQuad({ 1.0f,2.0f }, { 1.0F,1.0F }, W_Rockstairs[1]);
		Hazel::Renderer2D::DrawQuad({ 2.0f,2.0f }, { 1.0F,1.0F }, B_Rockstairs[0]);
		Hazel::Renderer2D::DrawQuad({ 3.0f,2.0f }, { 1.0F,1.0F }, B_Rockstairs[1]);
#endif


//batch rendering TEST
#if 0
		for (float i =-5.0f;i<5.0f;i+=0.5f)
		{
			for (float j = -5.0f; j <5.0f; j += 0.5f)
			{
				Hazel::Renderer2D::DrawQuad({ i, j,1.0f }, { 0.45f,0.45f }, { (i + 5.0f) / 10, 0.78f,(j + 5.0f) / 10 ,0.8f});
			}
		}
#endif	

		

//Á£×ÓÏµÍ³²âÊÔ		
#if 0
		if (Hazel::Input::IsMouseButtonPressed(0))
		{
			auto [x, y] = Hazel::Input::GetMousePosition();
			auto bounds = m_CameraController.GetBounds();
			auto width = Hazel::Application::Get().GetWindow().GetWidth();
			auto height = Hazel::Application::Get().GetWindow().GetHeight();
			auto pos = m_CameraController.GetOrthographicCamera().GetPosition();
			//Color
			/*
			float ColorR = Hazel::Random::Float();
			float ColorG = Hazel::Random::Float();
			float ColorB = Hazel::Random::Float();
			m_Particle.ColorBegin = { ColorR,ColorG,ColorB ,1.0 };
			ColorR = Hazel::Random::Float();
			ColorG = Hazel::Random::Float();
			ColorB = Hazel::Random::Float();
			m_Particle.ColorEnd = { ColorR,ColorG,ColorB ,1.0 };
			
			*/

			x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
			y = bounds.GetHeight() *0.5f - (y / height) * bounds.GetHeight();
			m_Particle.Position = { x + pos.x, y + pos.y };
			for (int i = 0; i < 50; i++)
				m_ParticleSys.Emit(m_Particle);
		}


		m_ParticleSys.OnUpdate(ts);
		m_ParticleSys.OnRender(m_CameraController.GetOrthographicCamera());
#endif 
		Hazel::Renderer2D::EndScene();

	}
}

void Sandbox2DLayer::OnEvent(Hazel::Event& e)
{
	HZ_PROFILE_FUCTION();
	m_CameraController.OnEvent(e);
}

void Sandbox2DLayer::OnImGuiRender()
{
	HZ_PROFILE_FUCTION();
	ImGui::Begin("setting");
	ImGui::Text("Render2DStats");
	ImGui::Text("DrawCalls: %d", Hazel::Renderer2D::GetStats().DrawCalls);
	ImGui::Text("QuadCount: %d", Hazel::Renderer2D::GetStats().QuadCount);
	ImGui::Text("TotalVertexCount: %d", Hazel::Renderer2D::GetStats().GetTotalVertexCount());
	ImGui::ColorEdit4("squar_color", glm::value_ptr(FlatColor));
	ImGui::ColorEdit4("ParticleColorB", glm::value_ptr(m_Particle.ColorBegin));
	ImGui::ColorEdit4("ParticleColorE", glm::value_ptr(m_Particle.ColorEnd));
	ImGui::DragFloat("Life Time", &m_Particle.LifeTime, 0.1f, 0.0f, 1000.0f);
	ImGui::End();

	
}

