#include "hzpch.h"
#include "Shader.h"

#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Hazel {

	Ref<Shader> Hazel::Shader::Create(const std::string& name, const std::string& VertexShader, const std::string& FragmentShader)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::NONE:    HZ_CORE_ASSERT(false, "RendererAPI::NONE is not support"); return nullptr;
		case RendererAPI::API::OPENGL:  return CreateRef<OpenGLShader>(name, VertexShader, FragmentShader);
		}
		HZ_CORE_ASSERT(false, "unknow RendererAPI");
		return nullptr;
	}
	Ref<Shader> Shader::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::NONE:    HZ_CORE_ASSERT(false, "RendererAPI::NONE is not support"); return nullptr;
		case RendererAPI::API::OPENGL:  return CreateRef<OpenGLShader>(path);
		}
		HZ_CORE_ASSERT(false, "unknow RendererAPI");
		return nullptr;
	}


	void ShaderLibrary::Add(Ref<Shader>& shader)
	{
		auto name = shader->GetName();
		Add(name,shader);
	}

	void ShaderLibrary::Add(const std::string& name, Ref<Shader>& shader)
	{
		HZ_CORE_ASSERT(!Exists(name), "shader already exists!");
		m_Shaders[name] = shader;
	}

	Hazel::Ref<Hazel::Shader> ShaderLibrary::Load(const std::string& Filepath)
	{
		auto Shader = Shader::Create(Filepath);
		Add(Shader);
		return Shader;
	}

	Hazel::Ref<Hazel::Shader> ShaderLibrary::Load(const std::string& name, const std::string& Filepath)
	{
		auto Shader = Shader::Create(Filepath);
		Add(name,Shader);
		return Shader;
	}

	Hazel::Ref<Hazel::Shader> ShaderLibrary::Get(const std::string& name)
	{
		HZ_CORE_ASSERT(Exists(name), "shader not exists!");
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}

}
