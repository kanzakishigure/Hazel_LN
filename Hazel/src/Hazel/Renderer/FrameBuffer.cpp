#include "hzpch.h"
#include "FrameBuffer.h"
#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLFrameBuffer.h"
namespace Hazel {

	Hazel::Ref<Hazel::FrameBuffer> FrameBuffer::Create(const FrameBufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::NONE:    HZ_CORE_ASSERT(false, "RendererAPI::NONE is not support"); return nullptr;
			case RendererAPI::API::OPENGL:  return CreateRef<OpenGLFrameBuffer>(spec);
		}
		HZ_CORE_ASSERT(false, "unknow RendererAPI");
		return nullptr;
	}

}