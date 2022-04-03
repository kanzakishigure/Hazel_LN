#pragma once
#include <string.h>
#include <glm/glm.hpp>
#include "Hazel/Renderer/Camera.h"
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
		Hazel::Camera Camera;
		bool Primary = true;
		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
		CameraComponent(Hazel::Camera camera)
			:Camera(camera)
		{}
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
}