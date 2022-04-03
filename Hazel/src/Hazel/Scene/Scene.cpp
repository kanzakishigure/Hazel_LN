#include "hzpch.h"

#include "Scene.h"
#include "glm/glm.hpp"
#include "Entity.h"
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
		
		
	}	

	

	Entity Scene::CreateEntity(const std::string name )
	{
		Entity e = { m_Rehistry.create(),this };
		e.AddComponent<TransformComponent>(glm::mat4(1.0f));
		auto& tag = e.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity": name;
		return e;
	}




}