#pragma once
#include "Renderer/FrameBuffer.h"

namespace Hazel
{
	class OpenGLFrameBuffer :public FrameBuffer
	{
	public: 
		OpenGLFrameBuffer(FrameBufferSpecification spec);
		virtual ~OpenGLFrameBuffer();

		void Invalidata() ;

		virtual void Bind()override;
		virtual void Unbind()override;

		virtual const FrameBufferSpecification& GetSpecification() const override { return m_Specification; }
		virtual uint32_t GetColorAttachmentRendererID() const override { return m_ColorAttachment; }
		virtual uint32_t GetDepthAttachmentRendererID() const override { return m_DepthAttachment; }

		virtual void Resize(uint32_t width, uint32_t height) override;
	private:
		FrameBufferSpecification m_Specification;
		uint32_t m_RendererID = 0;;
		//FrameBuffer×é¼þ
		uint32_t m_ColorAttachment = 0;
		uint32_t m_DepthAttachment = 0;
	};
}