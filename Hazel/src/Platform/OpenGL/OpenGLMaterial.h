#pragma once
#include "Renderer/Material.h"
#include "Hazel/Core/StorageBuffer.h"
#include "glm/glm.hpp"
namespace Hazel {
	//参照cherno的vulkan版材质类进行进行改写

	
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
		virtual void Set(const std::string& name, int value) override;

		virtual void SetIntArray(const std::string& name, const int count, const int* value) override;

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
	};
}