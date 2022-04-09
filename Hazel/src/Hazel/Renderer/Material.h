#pragma once
#include "Shader.h"
#include "Hazel/Core/Base.h"
namespace Hazel
{
	class Material
	{
	public:
		 Material(){}
		 virtual ~Material() {}
		 virtual const Ref<Shader> GetShader()const = 0;
	public:
		static Ref<Material> Create(const Ref<Shader>& shader,const std::string& name);

		
		virtual void Set(const std::string& name, const glm::mat4& value) = 0;
		virtual void Set(const std::string& name, float value) = 0;
		virtual void Set(const std::string& name, const glm::vec2& value) = 0;
		virtual void Set(const std::string& name, const glm::vec3& value) = 0;
		virtual void Set(const std::string& name, const glm::vec4& value) = 0;
		virtual void Set(const std::string& name, int value) = 0;

		virtual void SetIntArray(const std::string& name, const int count, const int* value) = 0;

		
		
	};
}