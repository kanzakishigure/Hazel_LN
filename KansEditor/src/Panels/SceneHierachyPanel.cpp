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

		{
			ImGui::Begin("SceneHierachyPanel:");
			m_Context->m_Registry.each([&](auto entityID)
				{
					Entity entity = { entityID ,m_Context.get() };
					DrawEntityNode(entity);
				});

			if (ImGui::IsMouseClicked(0) && ImGui::IsWindowHovered())
			{
				m_SelectionContext = {};
			}
			//create Entity
			if (ImGui::BeginPopupContextWindow(0,1,false))
			{
				if(ImGui::MenuItem("Create Entity"))
					m_Context->CreateEntity("Empty Entity");
				
				ImGui::EndPopup();
			}
			ImGui::End();
		} 
				
		{
			ImGui::Begin("Properties");
			if (m_SelectionContext)
			{
				DrawComponents(m_SelectionContext);
				ImGui::Separator();
				ImGui::SameLine(ImGui::GetWindowWidth()/3);
				if (ImGui::Button("Add Component",ImVec2(ImGui::GetWindowWidth() / 3,20)))
				{
					ImGui::OpenPopup("AddComponent");
				}
				if (ImGui::BeginPopup("AddComponent"))
				{
					if (ImGui::MenuItem("Sprite Component"))
					{
						auto& spritCMP = m_SelectionContext.AddComponent<SpriteRendererComponent>();
						spritCMP.Texture = Hazel::Texture2D::Create("F:/Kans3D/Hazel/KansEditor/assets/textures/Checkerboard.png");
						ImGui::CloseCurrentPopup();
					}
					if (ImGui::MenuItem("Mesh Component"))
					{
						auto& meshCMP = m_SelectionContext.AddComponent<MeshComponent>();
						auto MeshSrouce = CreateRef<MeshSource>("F:/Kans3D/Hazel/KansEditor/assets/model/ht/ht.fbx");
						auto Meshshader = Shader::Create("F:/Kans3D/Hazel/KansEditor/assets/shaders/StaticMeshShader.glsl");
						Meshshader->SetShaderBuffer({
							{ShaderDataType::Mat4,"U_ViewProjection"},
							{ShaderDataType::Mat4,"U_Transform"}
							});
						Ref<Material> StaticMeshShader = Material::Create(Meshshader, "StaticMesh_MTL");
						MeshSrouce->SetMaterial(StaticMeshShader);
						meshCMP.MeshSource = MeshSrouce;
					}
					if (ImGui::MenuItem("Camera Component"))
					{
						m_SelectionContext.AddComponent<CameraComponent>();
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}
			}
				
			ImGui::End();
		}
		
	}
	

	void SceneHierachyPanel::DrawEntityNode(Entity entity)
	{
		auto tag = entity.GetComponent<TagComponent>();
		
		ImGuiTreeNodeFlags flag = ( (m_SelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		//extend selectable area
		flag |= ImGuiTreeNodeFlags_SpanAvailWidth;

		bool opened =	ImGui::TreeNodeEx((void*)(uint32_t)(entity),flag,tag.Tag.c_str());
		
		if (ImGui::IsItemClicked())
		{
			m_SelectionContext = entity;
		}
		bool EntityDelete = false;
		//delete Entity
		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Delete Entity"))
			{
				EntityDelete = true;
			}
			ImGui::EndPopup();
		}
		if (opened)
		{
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
			bool opened = ImGui::TreeNodeEx((void*)7589654, flags, tag.Tag.c_str());
			if (opened)
			{
				ImGui::TreePop();
			}
			ImGui::TreePop();
		}
		if (EntityDelete)
		{
			m_Context->DeleteEntity(entity);
			if (m_SelectionContext == entity)
			{
				m_SelectionContext = {};
			}
		}
			
		
	}

	const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_DefaultOpen;
	void SceneHierachyPanel::DrawComponents(Entity entity)
	{
		if (entity.HasComponent<TagComponent>())
		{
			ImGui::Separator();

			auto& tag = entity.GetComponent<TagComponent>().Tag;
			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			strcpy_s(buffer, sizeof(buffer) ,tag.c_str());
			if (ImGui::InputText("##Tag", buffer, sizeof(buffer)),ImGuiInputTextFlags_AutoSelectAll)
			{
				tag = std::string(buffer);
			}
			ImGui::Separator();
			
		}

		KansUI::DrawComponent<TransformComponent>("Transform", entity, [](TransformComponent& component) {
			
			ImGui::Separator();
		
			KansUI::DrawVec3Control("Position", component.Position);

			glm::vec3  rotation = glm::degrees(component.Rotation);
			KansUI::DrawVec3Control("Rotation", rotation);
			component.Rotation = glm::radians(rotation);

			KansUI::DrawVec3Control("Scale", component.Scale, 1.0f);
			});	
		KansUI::DrawComponent<CameraComponent>("Camera", entity, [](CameraComponent& component) {
			auto& camera = component.SceneCamera;
			ImGui::Separator();
			ImGui::Checkbox("Isprimary", &component.Primary);
			ImGui::Checkbox("FixedAspectRatio", &component.FixedAspectRatio);
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
			});
		KansUI::DrawComponent<SpriteRendererComponent>("SpriteRenderer", entity, [](SpriteRendererComponent& component) {
			ImGui::Separator();
			auto& color = component.Color;
			ImGui::ColorEdit4("Color:", glm::value_ptr(color));
			ImGui::Separator();
			ImGui::Text("Texture path is : %s", component.Texture->GetPath().c_str());
		});
		KansUI::DrawComponent<MeshComponent>("Mesh", entity, [](MeshComponent& component) {
			ImGui::Separator();
			ImGui::Text("Mesh load path is: %s", component.MeshSource->GetLoadPath().c_str());
			ImGui::Separator();
			ImGui::Text("Mesh Material is: %s", component.MeshSource->GetMaterial()->GetName().c_str());
			});

	}
	

}

