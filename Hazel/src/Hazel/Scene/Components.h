#pragma once
#include <string.h>
#include <glm/glm.hpp>
#include "Hazel/Renderer/SceneCamera.h"
#include "Hazel/Scene/ScriptableEntity.h"
namespace Hazel 
{

	struct  TagComponent
	{
		std::string Tag;
		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(std::string tag)
			:Tag(tag)
		{}
		operator std::string& () { return Tag; }
	};
	struct  TransformComponent
	{
		glm::mat4 Transform = glm::mat4(1.0f);
		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(glm::mat4 transfrom)
			:Transform(transfrom)
		{}

		operator glm::mat4& () { return Transform; }
		operator const glm::mat4& () const { return Transform; }

	};
	struct CameraComponent
	{
		Hazel::SceneCamera SceneCamera;
		bool Primary = true;
		bool FixedAspectRatio =false;
		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	
	};
	struct SpriteRendererComponent
	{
		glm::vec4 Color = { 1.0f ,1.0f ,1.0f ,1.0f };
		//目前未实现texture
		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent& ) = default;
		SpriteRendererComponent(glm::vec4 color)
			:Color(color)
		{}
	};
	struct MeshComponent
	{
		glm::vec3* vertex;
	};

	struct NativeScriptComponent
	{
		ScriptableEntity* Instance = nullptr;
		std::function<void()> InstantiateFunction;
		std::function<void()> DestoryInstanceFunction;
		
		std::function<void(ScriptableEntity*)> OnCreateFunction;
		std::function<void(ScriptableEntity*, TimeStep)> OnUpdateFunction;
		std::function<void(ScriptableEntity*)> OnDestoryFunction;
		template<typename T>
		void Bind()
		{
			InstantiateFunction = [&]() {Instance = new T(); };
			DestoryInstanceFunction = [&]() {delete (T*)Instance; Instance = nullptr; };

			OnCreateFunction = [](ScriptableEntity* Instance) {((T*)Instance)->OnCreate(); };
			OnUpdateFunction = [](ScriptableEntity* Instance, TimeStep ts) {((T*)Instance)->OnUpdate(ts); };
			OnDestoryFunction = [](ScriptableEntity* Instance) {((T*)Instance)->OnDestory(); };

		}
	};
}