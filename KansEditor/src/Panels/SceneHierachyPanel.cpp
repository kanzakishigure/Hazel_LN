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
			});
		KansUI::DrawComponent<SpriteRendererComponent>("SpriteRenderer", entity, [](SpriteRendererComponent& component) {
			ImGui::Separator();
			auto& color = component.Color;
			ImGui::ColorEdit4("Color:", glm::value_ptr(color));
			ImGui::Separator();
			ImGui::Text("Texture path is : %s", component.Texture->GetPath().c_str());
		});
		
		KansUI::DrawComponent<DirLightComponent>("DirLight", entity, [](DirLightComponent& component) {
			ImGui::Separator();
			KansUI::DrawVec3Control("Direction", component.Direction);
			ImGui::ColorEdit3("Diffuse_Intensity",glm::value_ptr(component.Diffuse_Intensity));
			ImGui::ColorEdit3("Specular_Intensity", glm::value_ptr(component.Specular_Intensity));
			ImGui::ColorEdit3("Ambient_Intensity", glm::value_ptr(component.Ambient_Intensity));
			});
		KansUI::DrawComponent<PointLightComponent>("PointLight", entity, [](PointLightComponent& component) {
			ImGui::Separator();
			ImGui::ColorEdit3("Diffuse_Intensity", glm::value_ptr(component.Diffuse_Intensity));
			ImGui::ColorEdit3("Specular_Intensity", glm::value_ptr(component.Specular_Intensity));
			ImGui::ColorEdit3("Ambient_Intensity", glm::value_ptr(component.Ambient_Intensity));
			});
		KansUI::DrawComponent<StaticMeshComponent>("Mesh", entity, [](StaticMeshComponent& component) {
			ImGui::Separator();
			ImGui::Text("Mesh load path is: %s", component.StaticMesh->GetMeshSource()->GetLoadPath().c_str());
			});
		KansUI::DrawComponent<MaterialComponent>("Material", entity, [](MaterialComponent& component) {
			ImGui::Separator();
			const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_Framed
				| ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_FramePadding;
			auto materialCount = component.MaterialTable->GetMaterialCount();
			for (uint32_t i = 0; i < materialCount; i++)
			{
				ImGui::Separator();
				auto& material = component.MaterialTable->GetMaterialAsset(i)->GetMaterial();
				auto& materialBuffer = material->GetShaderBuffer();

				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
				auto contentregion = ImGui::GetContentRegionAvail();
				float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
				bool open = ImGui::TreeNodeEx((void*)i, treeNodeFlags, material->GetName().c_str());
				ImGui::PopStyleVar();
				
				if (open)
				{
					for (auto& UniformMap : materialBuffer.ShaderUniforms)
					{
						ImGui::Separator();
						const std::string& uniformName = UniformMap.first;
						auto& uniform = UniformMap.second;
						switch (uniform.GetType())
						{
						case ShaderDataType::Float:
						{
							float value = 0.0f;
							value = material->GetFloat(uniformName);
							std::string label = material->GetName() + "   " + uniformName;
							KansUI::DrawFloatControl(label, value);
							material->Set(uniformName, value);
						}
						break;
						case ShaderDataType::Float2:
						{
							glm::vec2 value = glm::vec2(1.0);
							value = material->GetVec2(uniformName);
							std::string label = material->GetName() + "   " + uniformName;
							KansUI::DrawVec2Control(label, value);
							material->Set(uniformName, value);
						}
						break;
						case ShaderDataType::Float3:
						{
							glm::vec3 value = glm::vec3(1.0);
							value = material->GetVec3(uniformName);
							std::string label = material->GetName() + "   " + uniformName;
							KansUI::DrawVec3Control(label, value);
							material->Set(uniformName, value);
						}
						break;
						case ShaderDataType::Float4:
						{
							glm::vec4 value = glm::vec4(1.0);
							value = material->GetVec4(uniformName);
							std::string label = material->GetName() + "   " + uniformName;
							KansUI::DrawVec4Control(label, value);
							material->Set(uniformName, value);
						}
						break;
						case ShaderDataType::Color4:
						{
							glm::vec4 value = glm::vec4(1.0);
							value = material->GetVec4(uniformName);
							std::string label = material->GetName() + "   " + uniformName;
							ImGui::ColorEdit4(label.c_str(), glm::value_ptr(value));
							material->Set(uniformName, value);
						}
						break;
						case ShaderDataType::Color3:
						{
							glm::vec3 value = glm::vec3(1.0);
							value = material->GetVec4(uniformName);
							std::string label = material->GetName() + "   " + uniformName;
							ImGui::ColorEdit3(label.c_str(), glm::value_ptr(value));
							material->Set(uniformName, value);
						}
						break;
						case ShaderDataType::Int2:
						{
							glm::ivec2 value = glm::ivec2(0);
							value = material->GetIVec2(uniformName);
							std::string label = material->GetName() + "   " + uniformName;
							ImGui::DragInt2(label.c_str(), glm::value_ptr(value),1,0,255);
							material->Set(uniformName, value);
						}
						break;

						}
						ImGui::NewLine();
					}
					ImGui::TreePop();
				}
			}
			
		}
	}
	

}

