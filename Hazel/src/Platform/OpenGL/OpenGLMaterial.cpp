#include "hzpch.h"
#include "OpenGLMaterial.h"
#include "OpenGLShader.h"
namespace Hazel {
	
	void OpenGLMaterial::Set(std::string name, int value)
	{
		//TODO:
		//��list�����ж�Ӧ��shader����Ҫ��ȫ�ֱ������и�ֵ
		//std::dynamic_pointer_cast<OpenGLShader>(m_Shaders.back())->UploadUniformInt(name,value);
	}
	void OpenGLMaterial::Set(std::string name, float value)
	{
		//TODO:
		//��list�����ж�Ӧ��shader����Ҫ��ȫ�ֱ������и�ֵ
		//std::dynamic_pointer_cast<OpenGLShader>(m_Shaders.back())->UploadUniformInt(name, value);
	}

	void OpenGLMaterial::Get() const
	{
	}
	

}