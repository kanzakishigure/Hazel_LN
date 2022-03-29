#pragma once
#include "Hazel/Renderer/VertexArray.h"

namespace Hazel {
	
	class OpenGLVertexArray: public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray()override;

		virtual void Bind()const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)   override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)  override;
		
		virtual const std::vector<Hazel::Ref<VertexBuffer>>& GetVertexBuffer()const override { return m_VertexBuffers; }
		virtual const Ref<IndexBuffer>& GetIndexBuffer()const override { return m_IndexBuffers; }

	private:
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffers;
		uint32_t m_RendererID;
	};
}