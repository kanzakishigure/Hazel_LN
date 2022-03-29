#include "hzpch.h"
#include "Hazel/Renderer/VertexArray.h"
#include "Hazel/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
namespace Hazel {


	Ref<VertexArray> VertexArray::Create()
	{
		
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::NONE:    HZ_CORE_ASSERT(false, "RendererAPI::NONE is not support"); return nullptr;
		case RendererAPI::API::OPENGL:  return  CreateRef<OpenGLVertexArray>();
		}
		HZ_CORE_ASSERT(false, "unknow RendererAPI");
		return nullptr;
	}

}