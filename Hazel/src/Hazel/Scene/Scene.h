#pragma once
#include <entt.hpp>
#include "Hazel/Core/TimeStep.h"
//
#include "hazel/Renderer/Mesh.h"
namespace  Hazel
{

	class Entity;

	class Scene
	{

	public:
		Scene();
		~Scene();

		const entt::registry& Reg() const { return m_Registry; }
		entt::registry& Reg() { return m_Registry; }

		void OnUpdate(TimeStep ts);
		void OnViewportResize(uint32_t width, uint32_t height);

		Entity CreateEntity(const std::string name = std::string());
		void DeleteEntity(Entity entity);
	private:
		template<typename T>
		void OnComponentAdd(Entity entity, T& component );
	private:
		entt::registry m_Registry;
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

		friend class Entity;
		friend class SceneHierachyPanel;
	};

	


}