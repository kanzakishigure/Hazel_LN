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
		
		//FrameBuffer init
		{
			FrameBufferSpecification spec;
			spec.Width = Application::Get().GetWindow().GetWidth();
			spec.Height = Application::Get().GetWindow().GetHeight();
			m_Framebuffer = FrameBuffer::Create(spec);

		}
	
		// scene init
		{
			m_ActiveScene = CreateRef<Scene>();
			squalEntity = m_ActiveScene->CreateEntity("SqualEntitu");
			squalEntity.AddComponent<SpriteRendererComponent>(FlatColor);

			m_CameraEntity = m_ActiveScene->CreateEntity("mainCamera");
			m_CameraEntity.AddComponent<CameraComponent>(glm::ortho(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

			m_SecondCameraEntity = m_ActiveScene->CreateEntity("SecondCamera");
			m_SecondCameraEntity.AddComponent<CameraComponent>(glm::ortho(-10.0f, 10.0f, -5.0f, 5.0f, -1.0f, 1.0f));
			m_SecondCameraEntity.GetComponent<CameraComponent>().Primary = false;

		}

		
	}

	void EditorLayer::OnDetach()
	{
		HZ_PROFILE_FUCTION();
		HZ_CORE_INFO("call detach");
		Renderer2D::Shutdown();

	}

	void EditorLayer::OnUpdate(TimeStep ts)
	{
		HZ_PROFILE_FUCTION();
		//update
		{
			if(!m_ViewportFocused)
			m_CameraController.OnUpdate(ts);

		}
		//renderer
		Renderer2D::ResetStats();
		m_Framebuffer->Bind();
		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		RenderCommand::Clear();
		
		//rendering
		{
			HZ_PROFILE_SCOPE("rendering")

			//updateScene
			m_ActiveScene->OnUpdate(ts);

			m_Framebuffer->Unbind();

		}
	}

	void EditorLayer::OnEvent(Event& e)
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
					Application::Get().Close();
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
			ImGui::Separator();
			//blockevent
			m_ViewportFocused = ImGui::IsWindowFocused();
			m_viewprotHovered = ImGui::IsWindowHovered();
			Application::Get().GetImGuiLayer()->BlockEvents(m_ViewportFocused||m_viewprotHovered);


			ImGui::Text("Render2DStats");
			ImGui::Text("DrawCalls: %d", Renderer2D::GetStats().DrawCalls);
			ImGui::Text("QuadCount: %d", Renderer2D::GetStats().QuadCount);
			ImGui::Text("TotalVertexCount: %d", Renderer2D::GetStats().GetTotalVertexCount());
			ImGui::Separator();

			if (squalEntity)
			{
				ImGui::Separator();
				ImGui::Text("Entity Tag :%s", squalEntity.GetComponent<TagComponent>().Tag.c_str());
				ImGui::ColorEdit4("squar_color", glm::value_ptr(FlatColor));
				squalEntity.GetComponent<SpriteRendererComponent>().Color = FlatColor;
				ImGui::Separator();
			}

			ImGui::Separator();
			
			ImGui::Checkbox("switch camera", &Switchcamera);
			ImGui::Separator();
			m_CameraEntity.GetComponent<CameraComponent>().Primary = Switchcamera;
			m_SecondCameraEntity.GetComponent<CameraComponent>().Primary = !Switchcamera;
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


