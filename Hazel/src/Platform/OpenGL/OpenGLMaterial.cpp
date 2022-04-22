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

	const std::string& OpenGLMaterial::GetName() const
	{
		return m_Name;
	}
	/// <summary>
	/// we should up date the data every frame
	/// </summary>
	void OpenGLMaterial::Invalidate()
	{

		//Set shader uniform 
		auto shaderUnifrom = m_Shader->GetShaderBuffer().ShaderUniforms;
		for (auto& key:shaderUnifrom)
		{
			auto& uniformbuffer = key.second;
			uint32_t offset = uniformbuffer.GetOffset();
			uint32_t size = uniformbuffer.GetSize();
			std::string name = uniformbuffer.GetName();
			switch (uniformbuffer.GetType())
			{
				case ShaderDataType::Float:  m_Shader->SetFloat(name, m_UniformBuffer.Read<float>(offset, size));     break;
				case ShaderDataType::Float2: m_Shader->SetFloat2(name, m_UniformBuffer.Read<glm::vec2>(offset, size)); break;
				case ShaderDataType::Float3: m_Shader->SetFloat3(name, m_UniformBuffer.Read<glm::vec3>(offset, size)); break;
				case ShaderDataType::Float4: m_Shader->SetFloat4(name, m_UniformBuffer.Read<glm::vec4>(offset, size)); break;
				case ShaderDataType::Mat4:   m_Shader->SetMat4(name, m_UniformBuffer.Read<glm::mat4>(offset, size));  break;
				case ShaderDataType::Int:	 m_Shader->SetInt(name, m_UniformBuffer.Read<int>(offset, size));		  break;
			}
		}
		//bug here can't bind texture;
		//set texture
		uint32_t TexSlot = 0;
		for (auto& key : m_Texture)
		{
			m_Shader->SetInt(key.first, TexSlot);
			key.second->Bind(TexSlot);
			TexSlot++;
		}
		
	}

	OpenGLMaterial::OpenGLMaterial(const Ref<Shader>& shader, const std::string& name /*= " "*/)
		:m_Shader(shader),m_Name(name)
	{
		Init();
	}

	OpenGLMaterial::~OpenGLMaterial()
	{
		m_UniformBuffer.Release();
		HZ_INFO("Release StorageBuffer in Material");
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
		Set<glm::mat4>(name,value);
	}

	void OpenGLMaterial::Set(const std::string& name, float value)
	{
		Set<float>(name, value);
	}

	void OpenGLMaterial::Set(const std::string& name, const glm::vec2& value)
	{
		Set<glm::vec2>(name, value);
	}

	void OpenGLMaterial::Set(const std::string& name, const glm::vec3& value)
	{
		Set<glm::vec3>(name, value);
	}

	void OpenGLMaterial::Set(const std::string& name, const glm::vec4& value)
	{
		Set<glm::vec4>(name, value);
	}

	void OpenGLMaterial::Set(const std::string& name, int value)
	{
		Set<int>(name, value);
	}

	void OpenGLMaterial::Set(const std::string& name, Ref<Texture2D> value)
	{
		m_Texture[name] = value;
	}

	ShaderUniform* OpenGLMaterial::FindUniform(const std::string& name)
	{

		const ShaderBuffer& shaderbuffer =  m_Shader->GetShaderBuffer();
		
		if (shaderbuffer.ShaderUniforms.size()>0)
		{
			if (shaderbuffer.ShaderUniforms.find(name) == shaderbuffer.ShaderUniforms.end())
			{
				HZ_WARN("can't find the uniform :({0}) in material:({1}) ", name.c_str(), m_Name.c_str());
				return nullptr;
			}
			auto& uniform = shaderbuffer.ShaderUniforms.at(name);
			return (ShaderUniform*)&(uniform);
		}
		return nullptr;
		
	}

}