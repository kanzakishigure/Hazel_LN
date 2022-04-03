#pragma once
#include <entt.hpp>

#include "Hazel/Core/TimeStep.h"
#include "Hazel/Scene/Components.h"

namespace  Hazel
{

	class Entity;

	class Scene
	{

	public:
		Scene();
		~Scene();

		const entt::registry& Reg() const { return m_Rehistry; }
		entt::registry& Reg() { return m_Rehistry; }

		void OnUpdate(TimeStep ts);
		void OnViewportResize(uint32_t width, uint32_t height);
		Entity CreateEntity(const std::string name = std::string());

	private:
		entt::registry m_Rehistry;

		friend class Entity;
	};

	


}