#include "hzpch.h"
#include "OpenGLMaterial.h"
#include "OpenGLShader.h"
namespace Hazel {
	
	
	void OpenGLMaterial::SetIntArray(const std::string& name, const int count, const int* value)
	{
		//TO DO 
		//push to buffer
		m_Shader->SetIntArray(name, count, value);
	}

	OpenGLMaterial::OpenGLMaterial(const Ref<Shader>& shader, const std::string& name /*= " "*/)
		:m_Shader(shader),m_Name(name)
	{
		Init();
	}

	OpenGLMaterial::~OpenGLMaterial()
	{
		m_UniformBuffer.Realse();
	}

	void OpenGLMaterial::Init()
	{

		AllocBuffer();
	}

	void OpenGLMaterial::AllocBuffer()
	{
		auto shaderbuffer = m_Shader->GetShaderBuffer();
		uint32_t size = shaderbuffer.Size;
		m_UniformBuffer.Allocate(size);
	}

	void OpenGLMaterial::Set(const std::string& name, const glm::mat4& value)
	{
		m_Shader->SetMat4(name, value);
		Set<glm::mat4>(name,value);
	}

	void OpenGLMaterial::Set(const std::string& name, float value)
	{
		m_Shader->SetFloat(name, value);
		Set<float>(name, value);
	}

	void OpenGLMaterial::Set(const std::string& name, const glm::vec2& value)
	{
		m_Shader->SetFloat2(name, value);
		Set<glm::vec2>(name, value);
	}

	void OpenGLMaterial::Set(const std::string& name, const glm::vec3& value)
	{
		m_Shader->SetFloat3(name, value);
		Set<glm::vec3>(name, value);
	}

	void OpenGLMaterial::Set(const std::string& name, const glm::vec4& value)
	{
		m_Shader->SetFloat4(name, value);
		Set<glm::vec4>(name, value);
	}

	void OpenGLMaterial::Set(const std::string& name, int value)
	{
		m_Shader->SetInt(name, value);
		Set<int>(name, value);
	}

	ShaderUniform* OpenGLMaterial::FindUniform(const std::string& name)
	{

		const ShaderBuffer& shaderbuffer =  m_Shader->GetShaderBuffer();
		
		if (shaderbuffer.ShaderUniforms.size()>0)
		{
			if (shaderbuffer.ShaderUniforms.find(name) == shaderbuffer.ShaderUniforms.end())
			{
				return nullptr;
			}
			auto& uniform = shaderbuffer.ShaderUniforms.at(name);
			return (ShaderUniform*)&(uniform);
		}
		return nullptr;
		
	}

}