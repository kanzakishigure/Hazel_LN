#pragma once
#include "Shader.h"
#include "Core/Core.h"
namespace Hazel
{
	class Material
	{
	public:
		 Material(){}
		virtual ~Material() = 0;
	public:
		static Ref<Material> Create(const Ref<Shader>& shader,const std::string& name);

		virtual void Set(std::string name,int value) = 0;
		virtual void Set(std::string name,float value) = 0;
		virtual void Get()const = 0;
	};
}