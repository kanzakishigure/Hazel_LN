#include "SceneHierachyPanel.h"
#include "Hazel/Scene/Components.h"
#include <glm/gtc/type_ptr.hpp>
namespace Hazel
{

	SceneHierachyPanel::SceneHierachyPanel(const Ref<Scene>& scene)
	{
		SetContext(scene);
	}

	void SceneHierachyPanel::SetContext(const Ref<Scene>& context)
	{
		m_Context = context;
	}

	void SceneHierachyPanel::OnImguiRender()
	{


			ImGui::Begin("SceneHierachyPanel:");
			m_Context->m_Rehistry.each([&](auto entityID)
				{

					Entity entity = { entityID ,m_Context.get() };
					DrawEntityNode(entity);
				});
			//ImGui::ShowDemoWindow();
			if (ImGui::IsMouseClicked(0) && ImGui::IsWindowHovered())
			{
				m_SelectionContext = {};
			}
			ImGui::End();
		
			
		{
			ImGui::Begin("Properties");
			if (m_SelectionContext)
				DrawComponents(m_SelectionContext);
			ImGui::End();
		}
		
	}
	

	void SceneHierachyPanel::DrawEntityNode(Entity entity)
	{
		auto tag = entity.GetComponent<TagComponent>();
		
		ImGuiTreeNodeFlags flag = ( (m_SelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;

		bool open =	ImGui::TreeNodeEx((void*)(uint32_t)(entity),flag,tag.Tag.c_str());
		
		if (ImGui::IsItemClicked())
		{
			m_SelectionContext = entity;
		}
		if (open)
		{
			ImGui::TreePop();
		}
		
	}

	void SceneHierachyPanel::DrawComponents(Entity entity)
	{
		if (entity.HasComponent<TagComponent>())
		{
			ImGui::Separator();

			auto& tag = entity.GetComponent<TagComponent>().Tag;
			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			strcpy_s(buffer, sizeof(buffer) ,tag.c_str());
			if (ImGui::InputText("Tag:", buffer, sizeof(buffer)),ImGuiInputTextFlags_AutoSelectAll)
			{
				tag = std::string(buffer);
			}
			ImGui::Separator();
			
		}
		if (entity.HasComponent<TransformComponent>())
		{
			if (ImGui::TreeNodeEx("TransformComponent"))
			{
				ImGui::Separator();
				auto& transformCMP = entity.GetComponent<TransformComponent>();
				if (ImGui::DragFloat3("Tranform", glm::value_ptr(transformCMP.Transform[3]), 0.5f))
				{
					//if matrix is change,than calculate the rotation,scale,translate;
				}
				ImGui::Separator();
				ImGui::TreePop();
			}
			
		}
		if (entity.HasComponent<CameraComponent>())
		{
			if (ImGui::TreeNodeEx("CameraComponent"))
			{
				ImGui::Separator();
				ImGui::LabelText("CameraComponent", "");
				auto& cameraCMP = entity.GetComponent<CameraComponent>();
				ImGui::Text("%s", ((bool)cameraCMP.SceneCamera.GetProjectionType()) ? "Orthographic" : "Perspective");
				ImGui::Text("%f", cameraCMP.SceneCamera.GetAspectRatio());
				ImGui::Separator();
				ImGui::TreePop();
			}
			
		}
		if (entity.HasComponent<SpriteRendererComponent>())
		{
			if (ImGui::TreeNodeEx("SpriteRendererComponent"))
			{
				ImGui::Separator();
				ImGui::LabelText("SpriteRendererComponent", "");
				auto& color = entity.GetComponent<SpriteRendererComponent>().Color;
				ImGui::DragFloat4("Color:", glm::value_ptr(color));
				ImGui::Separator();
				ImGui::TreePop();
			}
			
		}
	}
	

}

