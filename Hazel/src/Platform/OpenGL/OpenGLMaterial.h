#pragma once
#include <glm/glm.hpp>
#include "Renderer/Material.h"
#include "Hazel/Core/StorageBuffer.h"
#include "Hazel/Renderer/Texture.h"
namespace Hazel {
	//����cherno��vulkan���������н��и�д

	
	class OpenGLMaterial :public Material
	{
	public:
		OpenGLMaterial(const Ref<Shader>& shader, const std::string& name = " ");
		 ~OpenGLMaterial();

		void Init();
		void AllocBuffer();
		virtual const Ref<Shader> GetShader()const override { return m_Shader;}
		virtual void Set(const std::string& name, const glm::mat4& value) override;
		virtual void Set(const std::string& name, float value) override;
		virtual void Set(const std::string& name, const glm::vec2& value) override;
		virtual void Set(const std::string& name, const glm::vec3& value) override;
		virtual void Set(const std::string& name, const glm::vec4& value) override;
		virtual void Set(const std::string& name, bool value)  override;

		virtual void Set(const std::string& name, int value) override;
		virtual void Set(const std::string& name, const glm::ivec2& value) override;
		virtual void SetIntArray(const std::string& name, const int count, const int* value) override;
		virtual const std::string& GetName()const override;

		virtual void Set(const std::string& name, Ref<Texture2D> value) override;

		virtual glm::mat4& GetMat4(const std::string& name) override;
		virtual float& GetFloat(const std::string& name)     override;
		virtual glm::vec2& GetVec2(const std::string& name)  override;
		virtual glm::vec3& GetVec3(const std::string& name)  override;
		virtual glm::vec4& GetVec4(const std::string& name)  override;
		virtual int& GetInt(const std::string& name)         override;
		virtual glm::ivec2& GetIVec2(const std::string& name) override;
		
	public:
		
		template <typename T>
		void Set(const std::string& name, const T& value)
		{
			auto uniform = FindUniform(name);
			if (!uniform)
			{
				HZ_ASSERT(uniform, "Can not find uniform");
				return;
			}
			m_UniformBuffer.Write((byte*)&value,  uniform->GetOffset(), uniform->GetSize());
		}
		template <typename T>
		void Get(const std::string& name)
		{
			auto uniform = FindUniform(name);
			if (!uniform)
			{
				HZ_ASSERT(uniform, "Can not find uniform");
				return;
			}
			m_UniformBuffer.Read(uniform->GetOffset(),uniform->GetSize());
		}
	private: 
		ShaderUniform* FindUniform(const std::string& name);
	private:
		Ref<Shader> m_Shader;
		std::string m_Name;
		StorageBuffer m_UniformBuffer;
		//texure 
		std::map<std::string, Ref<Texture2D>> m_Texture;
	};
}
