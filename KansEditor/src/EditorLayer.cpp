#include "EditorLayer.h"
#include <imgui.h>
#include "Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const int S_mapwidth = 24;
static const char* S_mapTiles= "";
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Hazel
{


	EditorLayer::EditorLayer()
		:m_CameraController(1920.0f / 1080.0f), Layer("EditorLayer")
	{

	}


	void EditorLayer::OnAttach()
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
		m_Particle.SizeBegin = 0.5f, m_Particle.SizeVariation = 0.3f, m_Particle.SizeEnd = 0.0f;
		m_Particle.LifeTime = 1.5f;
		m_Particle.Velocity = { 0.0f, 0.0f };
		m_Particle.VelocityVariation = { 6.0f, 2.0f };
		m_Particle.Position = { 0.0f, 0.0f };
	}

	void EditorLayer::OnDetach()
	{
		HZ_PROFILE_FUCTION();
		HZ_CORE_INFO("call detach");
		Hazel::Renderer2D::Shutdown();

	}

	void EditorLayer::OnUpdate(Hazel::TimeStep ts)
	{
		HZ_PROFILE_FUCTION();
		//update
		{
			if(!m_ViewportFocused)
			m_CameraController.OnUpdate(ts);

		}
		Hazel::Renderer2D::ResetStats();
		m_Framebuffer->Bind();
		//rendererprep
		{
			//HazelTools::InstrumentationTimer timer();
			Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
			Hazel::RenderCommand::Clear();


		}
		//rendering
		{
			static float stride = 0;
			stride += ts;
			HZ_PROFILE_SCOPE("rendering");
			Hazel::Renderer2D::BeginScene(m_CameraController.GetOrthographicCamera());


			//transfrom Test
#if 0
			Hazel::Renderer2D::DrawQuad({ 1.0f,1.0f }, { 2.0f,2.0f }, glm::vec4(153.0f / 256, 90.0f / 256, 102.0f / 256, 1.0f));
			Hazel::Renderer2D::DrawQuad({ -1.0f,-1.0f }, { 2.0f,2.0f }, glm::vec4(103.0f / 256, 120.0f / 256, 102.0f / 256, 1.0f));
			Hazel::Renderer2D::DrawRotateQuad({ 0.0f,0.0f }, stride, { 4.0f,4.0f }, glm::vec4(130.0f / 256, 160.0f / 256, 30.0f / 256, 1.0f));

			Hazel::Renderer2D::DrawQuad({ 0.0f, 0.0f,-0.1f }, { 10.0f,10.0f }, FlatColor);


			Hazel::Renderer2D::DrawQuad({ 0.0f,0.0f,0.0f }, { 8.0f,4.5f }, LightPop);
#endif


			// texturesheet TEST
#if 0
			Hazel::Renderer2D::DrawQuad({ 0.0f,0.0f }, { 2.0f,3.0f }, Y_roof[0]);
			Hazel::Renderer2D::DrawQuad({ 0.0f,2.0f }, { 1.0F,1.0F }, W_Rockstairs[0]);
			Hazel::Renderer2D::DrawQuad({ 1.0f,2.0f }, { 1.0F,1.0F }, W_Rockstairs[1]);
			Hazel::Renderer2D::DrawQuad({ 2.0f,2.0f }, { 1.0F,1.0F }, B_Rockstairs[0]);
			Hazel::Renderer2D::DrawQuad({ 3.0f,2.0f }, { 1.0F,1.0F }, B_Rockstairs[1]);
#endif


			//batch rendering TEST
#if 1
			for (float i = -5.0f; i < 5.0f; i += 0.5f)
			{
				for (float j = -5.0f; j < 5.0f; j += 0.5f)
				{
					Hazel::Renderer2D::DrawQuad({ i, j,1.0f }, { 0.45f,0.45f }, { (i + 5.0f) / 10, 0.78f,(j + 5.0f) / 10 ,0.8f });
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
				y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
				m_Particle.Position = { x + pos.x, y + pos.y };
				for (int i = 0; i < 50; i++)
					m_ParticleSys.Emit(m_Particle);
			}


			m_ParticleSys.OnUpdate(ts);
			m_ParticleSys.OnRender(m_CameraController.GetOrthographicCamera());
#endif 
			Hazel::Renderer2D::EndScene();
			m_Framebuffer->Unbind();

		}
	}

	void EditorLayer::OnEvent(Hazel::Event& e)
	{
		HZ_PROFILE_FUCTION();
		m_CameraController.OnEvent(e);
	}

	void EditorLayer::OnImGuiRender()
	{
		HZ_PROFILE_FUCTION();

//imgui docking code
#if 1
		static bool p_open = true;
		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->GetWorkPos());
			ImGui::SetNextWindowSize(viewport->GetWorkSize());
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &p_open, window_flags);
		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}


		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Options"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows,
				// which we can't undo at the moment without finer window depth/z control.
				ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
				ImGui::MenuItem("Padding", NULL, &opt_padding);
				ImGui::Separator();

				if (ImGui::MenuItem("Flag: NoSplit", "", (dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoSplit; }
				if (ImGui::MenuItem("Flag: NoResize", "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
				if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode; }
				if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
				if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, opt_fullscreen)) { dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
				ImGui::Separator();

				if (ImGui::MenuItem("Close", NULL, false, &p_open != NULL))
				{
					p_open = false;
					Hazel::Application::Get().Close();
				}
				ImGui::EndMenu();
			}


			ImGui::EndMenuBar();
		}
		ImGui::End();
#endif


	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		{
			ImGui::Begin("ProjectSpecication");
			//blockevent
			m_ViewportFocused = ImGui::IsWindowFocused();
			m_viewprotHovered = ImGui::IsWindowHovered();
			Application::Get().GetImGuiLayer()->BlockEvents(m_ViewportFocused||m_viewprotHovered);

			ImGui::Text("Render2DStats");
			ImGui::Text("DrawCalls: %d", Hazel::Renderer2D::GetStats().DrawCalls);
			ImGui::Text("QuadCount: %d", Hazel::Renderer2D::GetStats().QuadCount);
			ImGui::Text("TotalVertexCount: %d", Hazel::Renderer2D::GetStats().GetTotalVertexCount());
			ImGui::ColorEdit4("squar_color", glm::value_ptr(FlatColor));
			ImGui::ColorEdit4("ParticleColorB", glm::value_ptr(m_Particle.ColorBegin));
			ImGui::ColorEdit4("ParticleColorE", glm::value_ptr(m_Particle.ColorEnd));
			ImGui::DragFloat("Life Time", &m_Particle.LifeTime, 0.1f, 0.0f, 1000.0f);
			uint32_t renderid = HuTao->GetRenererID();
			ImGui::Image((void*)renderid, ImVec2{ 269,232 }, ImVec2(-1, 1), ImVec2(0, 0));
			ImGui::End();

		}
		
		//colorbuffer
		{

			
			ImGui::Begin("ViewPort1");
			ImVec2 viewportsize = ImGui::GetContentRegionAvail();
			if (m_ViewportSize != *(glm::vec2*) & viewportsize)
			{
				
				m_ViewportSize = { viewportsize.x,viewportsize.y };
				m_Framebuffer->Resize((uint32_t)viewportsize.x, (uint32_t)viewportsize.y);
				m_CameraController.OnResize((uint32_t)viewportsize.x, (uint32_t)viewportsize.y);
			}
			uint32_t colorframebufferID = m_Framebuffer->GetColorAttachmentRendererID();
			ImGui::Image((void*)colorframebufferID, viewportsize, ImVec2(0, 1), ImVec2(1, 0));

			ImGui::End();
		}

		//depthbuffer
		{
			ImGui::Begin("ViewPort2");
			ImVec2 viewportsize = ImGui::GetContentRegionAvail();

			if (m_ViewportSize != *(glm::vec2*) & viewportsize)
			{
				//HZ_INFO("ViewportSize:  {0}   {1}", viewportsize.x, viewportsize.y);
				m_ViewportSize = { viewportsize.x,viewportsize.y };
				m_Framebuffer->Resize(viewportsize.x, viewportsize.y);
			}


			uint32_t depthframebufferID = m_Framebuffer->GetDepthAttachmentRendererID();
			ImGui::Image((void*)depthframebufferID, viewportsize, ImVec2(0, 1), ImVec2(1, 0));

			ImGui::End();
		}

	ImGui::PopStyleVar();
		


	}

}


