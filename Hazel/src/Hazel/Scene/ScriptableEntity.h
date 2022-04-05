#pragma once

#include "Hazel/Scene/Entity.h"
namespace Hazel
{
	class ScriptableEntity
	{
	public:
		template <typename T>
		T& GetComponent()
		{
			return m_Entity.GetComponent<T>();
		}
	protected:
		virtual void OnUpdate(TimeStep ts){}
		virtual void OnCreate(){}
		virtual void OnDestory(){}
	private:
		Entity m_Entity;
		friend class Scene;
	};

}