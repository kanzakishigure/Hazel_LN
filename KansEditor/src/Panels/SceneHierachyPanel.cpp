#include "SceneHierachyPanel.h"
#include "Hazel/Scene/Components.h"
#include <glm/gtc/type_ptr.hpp>
#include "Hazel/Utilities/KansUI.h"
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

				KansUI::DrawVec3Control("Position",transformCMP.Position);
				
				glm::vec3  rotation = glm::degrees(transformCMP.Rotation);
				KansUI::DrawVec3Control("Rotation",rotation);
				transformCMP.Rotation = glm::radians(rotation);
				
				KansUI::DrawVec3Control("Scale", transformCMP.Scale,1.0f);
				
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
				auto& camera = entity.GetComponent<CameraComponent>().SceneCamera;
				ImGui::Checkbox("Isprimary", &cameraCMP.Primary);
				ImGui::Checkbox("FixedAspectRatio", &cameraCMP.FixedAspectRatio);
				char* projectiontype[] = { "Perspective","Orthographic" };
				char* curentprojectstring = projectiontype[(int)camera.GetProjectionType()];
				if (ImGui::BeginCombo("Camera ProjectionType", curentprojectstring))
				{
					
					for (int i = 0; i < 2; i++)
					{
						bool isSelected = curentprojectstring == projectiontype[i];
						if (ImGui::Selectable(projectiontype[i], isSelected))
						{
							curentprojectstring = projectiontype[i];
							camera.SetProjectionType((SceneCamera::ProjectionType)i);
						}
						if (isSelected)
							ImGui::SetItemDefaultFocus();
					}
					ImGui::EndCombo();
				}
				//Perspective
				if (camera.GetProjectionType() == SceneCamera::ProjectionType::Perspective)
				{
					//VerticalFOV
					{
						float verticalFOV = camera.GetPerspectiveVerticalFOV();
						if (ImGui::DragFloat("VerticalFOV", &verticalFOV))
						{
							camera.SetPerspectiveVerticalFOV(verticalFOV);
						}
					}
					//Near Clip
					{
						float nearClip = camera.GetPerspectiveNearClip();
						if (ImGui::DragFloat("Near Clip", &nearClip))
						{
							camera.SetPerspectiveNearClip(nearClip);
						}
					}					
					//Far Clip
					{
						float farClip = camera.GetPerspectiveFarClip();
						if (ImGui::DragFloat("Far Clip", &farClip))
						{
							camera.SetPerspectiveFarClip(farClip);
						}
					}
					//Exposure
					{
						float exposure = camera.GetExposure();
						if (ImGui::DragFloat("Exposure", &exposure))
						{
							camera.SetExposure(exposure);
						}
					}
				
				}
				//Orthographic
				if (camera.GetProjectionType() == SceneCamera::ProjectionType::Orthographic)
				{
					//Size
					{
						float size = camera.GetOrthographicSize();
						if (ImGui::DragFloat("Size", &size))
						{
							camera.SetOrthographicSize(size);
						}
					}
					//Near Clip
					{
						float nearClip = camera.GetOrthographicNearClip();
						if (ImGui::DragFloat("Near Clip", &nearClip))
						{
							camera.SetOrthographicNearClip(nearClip);
						}
					}
					//Far Clip
					{
						float farClip = camera.GetOrthographicFarClip();
						if (ImGui::DragFloat("Far Clip", &farClip))
						{
							camera.SetOrthographicFarClip(farClip);
						}
					}
					//Exposure
					{
						float exposure = camera.GetExposure();
						if (ImGui::DragFloat("Exposure", &exposure))
						{
							camera.SetExposure(exposure);
						}
					}
					
				}
				ImGui::Separator();
				ImGui::TreePop();
			}
			
		}
		if (entity.HasComponent<SpriteRendererComponent>())
		{
			if (ImGui::TreeNodeEx("SpriteRendererComponent"))
			{
				ImGui::Separator();
				auto& colorCMP = entity.GetComponent<SpriteRendererComponent>();
				auto& color = colorCMP.Color;
				ImGui::ColorEdit4("Color:", glm::value_ptr(color));
				ImGui::Separator();
				ImGui::Text("Texture source Path: %s",colorCMP.Texture->GetPath().c_str());
				ImGui::TreePop();
			}
			
		}
	}
	

}

