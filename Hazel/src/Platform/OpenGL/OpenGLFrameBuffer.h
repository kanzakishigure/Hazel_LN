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
		virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const override;
		virtual uint32_t GetDepthAttachmentRendererID() const override { return m_DepthAttachment; }

		virtual void Resize(uint32_t width, uint32_t height) override;
	private:
		FrameBufferSpecification m_Specification;
		uint32_t m_RendererID = 0;;
		
		//FrameBufferFormat
		std::vector<FrameBufferTextureSpecification> m_ColorAttachmentSpecifications;
		FrameBufferTextureSpecification m_DepthAttachmentpecification;

		//Real FrameBuffer Attachment
		std::vector<uint32_t> m_ColorAttachments;
		uint32_t m_DepthAttachment = 0;
	};
}