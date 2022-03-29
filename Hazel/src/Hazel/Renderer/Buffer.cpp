#include "hzpch.h"
#include "Buffer.h"
#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
namespace Hazel {


	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::NONE:    HZ_CORE_ASSERT(false, "RendererAPI::NONE is not support"); return nullptr;
		case RendererAPI::API::OPENGL:  return CreateScope<OpenGLVertexBuffer>(vertices, size);
		}
		HZ_CORE_ASSERT(false, "unknow RendererAPI");
		return nullptr;
	}



	Ref<Hazel::VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::NONE:    HZ_CORE_ASSERT(false, "RendererAPI::NONE is not support"); return nullptr;
		case RendererAPI::API::OPENGL:  return CreateScope<OpenGLVertexBuffer>(size);
		}
		HZ_CORE_ASSERT(false, "unknow RendererAPI");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::NONE:    HZ_CORE_ASSERT(false, "RendererAPI::NONE is not support"); return nullptr;
		case RendererAPI::API::OPENGL:  return CreateScope<OpenGLIndexBuffer>(indices, count);;
		}
		HZ_CORE_ASSERT(false, "unknow RendererAPI");
		return nullptr;
	}

}
