#include "hzpch.h"

#include <glm/glm.hpp>
#include "Scene.h"
#include "Entity.h"
#include "Components.h"
#include "Hazel/Renderer/Renderer2D.h"
#include "Hazel/Renderer/Renderer.h"

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
			
			m_Registry.view<NativeScriptComponent>().each([=](auto entity,auto& nsc) {
				
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
		//Renderer preparation
		{
			//HazelTools::InstrumentationTimer timer();
			auto group = m_Registry.group<>(entt::get<TransformComponent,CameraComponent>);
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
#if 1
	if(maincamera!=nullptr)
		{
			Renderer2D::BeginScene(maincamera->GetProjectMatrix(), *Cameratransform);
			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto entity : group)
			{
				auto [transformCMP, spriteRendererCMP] = group.get(entity);
				Renderer2D::DrawQuad(transformCMP.GetTransform(), spriteRendererCMP.Texture, spriteRendererCMP.Color);

			}
			Renderer2D::EndScene();
		}
#endif
#if 1
	    //StaticMesh renderer
		if (maincamera != nullptr)
		{
			Renderer::BeginScene(maincamera->GetProjectMatrix(), *Cameratransform);

			auto group = m_Registry.view<TransformComponent, StaticMeshComponent>();
			for (auto entity: group)
			{
				auto [transformCMP, meshCMP] = group.get(entity);
				Renderer::Submit(meshCMP.StaticMesh ,transformCMP.GetTransform());
			}
			
			Renderer::EndScene();
		}
#endif		
		
	}	

	

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{

		m_ViewportWidth = width;
		m_ViewportHeight = height;

		auto view = m_Registry.view<CameraComponent>();
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
		Entity e = { m_Registry.create(),this };
		e.AddComponent<TransformComponent>();
		auto& tag = e.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity": name;
		return e;
	}

	void Scene::DeleteEntity(Entity entity)
	{
		m_Registry.destroy(entity);
	}
	//To use entt use the call back function we should implement the function advance
	template<typename T>
	void Scene::OnComponentAdd(Entity entity, T& component)
	{
		static_assert(false);
	}




	template<>
	void Scene::OnComponentAdd<CameraComponent>(Entity entity, CameraComponent& component)
	{
		if (m_ViewportWidth > 0 && m_ViewportHeight > 0)
			component.SceneCamera.SetViewportSize(m_ViewportWidth, m_ViewportHeight);
	}
	
	template<>
	void Scene::OnComponentAdd<TransformComponent>(Entity entity, TransformComponent& component)
	{

	}
	template<>
	void Scene::OnComponentAdd<StaticMeshComponent>(Entity entity, StaticMeshComponent& component)
	{

	}
	template<>
	void Scene::OnComponentAdd<TagComponent>(Entity entity, TagComponent& component)
	{

	}
	template<>
	void Scene::OnComponentAdd<NativeScriptComponent>(Entity entity, NativeScriptComponent& component)
	{

	}
	template<>
	void Scene::OnComponentAdd<SpriteRendererComponent>(Entity entity, SpriteRendererComponent& component)
	{

	}


}