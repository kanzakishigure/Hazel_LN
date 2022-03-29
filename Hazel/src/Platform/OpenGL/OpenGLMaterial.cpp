#include "hzpch.h"
#include "OpenGLMaterial.h"
#include "OpenGLShader.h"
namespace Hazel {
	
	void OpenGLMaterial::Set(std::string name, int value)
	{
		//TODO:
		//将list容器中对应的shader所需要的全局变量进行赋值
		//std::dynamic_pointer_cast<OpenGLShader>(m_Shaders.back())->UploadUniformInt(name,value);
	}
	void OpenGLMaterial::Set(std::string name, float value)
	{
		//TODO:
		//将list容器中对应的shader所需要的全局变量进行赋值
		//std::dynamic_pointer_cast<OpenGLShader>(m_Shaders.back())->UploadUniformInt(name, value);
	}

	void OpenGLMaterial::Get() const
	{
	}
	

}