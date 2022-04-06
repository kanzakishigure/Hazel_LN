#include "hzpch.h"

#include "Scene.h"
#include "glm/glm.hpp"
#include "Entity.h"
#include "Components.h"
#include "Hazel/Renderer/Renderer2D.h"


namespace Hazel
{	

	Scene::Scene()
	{

	}

	Scene::~Scene()
	{

	}

	void Scene::OnUpdate(TimeStep ts)
	{

		//update ScripteableEntity
		{
			
			m_Rehistry.view<NativeScriptComponent>().each([=](auto entity,auto& nsc) {
				
				if (!nsc.Instance)
				{
					nsc.Instance =  nsc.InstantiateFunction();
					nsc.Instance->m_Entity = Entity{ entity,this };
					nsc.Instance->OnCreate();
				}
				
				nsc.Instance->OnUpdate(ts);
				nsc.Instance->OnDestory();
				nsc.DestoryInstanceFunction(&nsc);
				});
		
		}

		Camera* maincamera = nullptr;
		glm::mat4* Cameratransform = nullptr ;
		//rendererprep
		{
			//HazelTools::InstrumentationTimer timer();
			auto group = m_Rehistry.group<>(entt::get<TransformComponent,CameraComponent>);
			for (auto entity : group)
			{
				auto [transformCMP, cameraCMP] = group.get(entity);
				if (cameraCMP.Primary)
				{
					maincamera = &cameraCMP.SceneCamera;
					Cameratransform = &transformCMP.GetTransform();
				}
				
			}
		}

		//ScenenRenderer2D
		if(maincamera!=nullptr)
		{
			Renderer2D::BeginScene(maincamera->GetProjectMatrix(), *Cameratransform);
			auto group = m_Rehistry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto entity : group)
			{
				auto [transformCMP, spriteRendererCMP] = group.get(entity);
				Renderer2D::DrawQuad(transformCMP.GetTransform(), spriteRendererCMP.Texture, spriteRendererCMP.Color);
			}
			Renderer2D::EndScene();

		}

		
	}	

	

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		auto view = m_Rehistry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& cameraCMP = view.get<CameraComponent>(entity);
			if (!cameraCMP.FixedAspectRatio)
			{
				cameraCMP.SceneCamera.SetViewportSize(width, height);
			}
			
		}
	}

	Entity Scene::CreateEntity(const std::string name)
	{
		Entity e = { m_Rehistry.create(),this };
		e.AddComponent<TransformComponent>();
		auto& tag = e.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity": name;
		return e;
	}




}