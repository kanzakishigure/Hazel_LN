#pragma once
#include "Hazel/Core/Core.h"

namespace Hazel {

	struct  FrameBufferSpecification
	{
		uint32_t Width, Height;
		uint32_t Samples = 1;

		bool SwapChainTarget = false;
		//glBindFramebuffer(0)
		//是否将该FrameBuffer渲染到屏幕
	};
	class FrameBuffer {
	public:
		static Ref<FrameBuffer> Create(const FrameBufferSpecification& spec);

		virtual const FrameBufferSpecification& GetSpecification() const = 0;
		virtual uint32_t GetColorAttachmentRendererID() const = 0;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

	private:
	};

}