#include "hzpch.h"
#include "Material.h"
#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLMaterial.h"

namespace Hazel
{

 Ref<Material> Material::Create(const Ref<Shader>& shader,const std::string& name)
{
	switch (Renderer::GetAPI())
	{
	case RendererAPI::API::NONE:    HZ_CORE_ASSERT(false, "RendererAPI::NONE is not support"); return nullptr;
	case RendererAPI::API::OPENGL:  std::make_shared<OpenGLMaterial>(shader,name);
	}
	HZ_CORE_ASSERT(false, "unknow RendererAPI");
	return nullptr;
}


}

