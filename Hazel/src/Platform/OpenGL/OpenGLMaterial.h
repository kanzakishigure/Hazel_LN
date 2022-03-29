#pragma once
#include "Renderer/Material.h"
namespace Hazel {
	//参照cherno的vulkan版材质类进行进行改写
	class OpenGLMaterial :public Material
	{
	public:
		OpenGLMaterial(const Ref<Shader>& shader,const std::string& name =" " )
			:m_Shader(shader),m_Name(name)
		{

		}
		virtual ~OpenGLMaterial() {};
		virtual void Set(std::string name,int value) override ;
		virtual void Set(std::string name,float value) override;
		virtual void Get()const override;
	private:
		Ref<Shader> m_Shader;
		std::string m_Name;
	};
}