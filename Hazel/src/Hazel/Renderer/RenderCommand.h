#pragma once
#include "RendererAPI.h"
namespace Hazel {

	class RenderCommand
	{
	public:
		//RenderCommand内部应该满足单一职责原则，不应该实现多余的功能，导致过藕合
		inline static void SetClearColor(const glm::vec4& color) 
		{
			s_RnedererAPI->SetClearColor(color);
		}
		inline static void Clear() 
		{	
			s_RnedererAPI->Clear();
		}
		inline static void  DrawIndexed(const Ref<VertexArray>& vertexArray,uint32_t indexCount=0)
		{
			s_RnedererAPI->DrawIndexed(vertexArray,indexCount);
		}
		inline static void Init() 
		{
			s_RnedererAPI->Init();
		}
		inline static void SetViewPort(uint32_t x, uint32_t y,uint32_t width, uint32_t height)
		{
			s_RnedererAPI->SetViewPort(x, y, width, height);
		}
		inline static void EnableSetStencil(bool enabled)
		{
			s_RnedererAPI->EnableSetStencil(enabled);
		}
		inline static void EnableDepthTest(bool enabled)
		{
			s_RnedererAPI->EnableDepthTest(enabled);
		}
		inline static void SetStencilFunc(StencilFunction func, uint32_t value, uint32_t mask)
		{
			s_RnedererAPI->SetStencilFunc(func,value,mask);
		}
		inline static void SetStencilMask(uint32_t mask) 
		{
			s_RnedererAPI->SetStencilMask(mask);
		}
		inline static void StencilOp(StencilOption sfail, StencilOption dpfail, StencilOption dppass)
		{
			s_RnedererAPI->StencilOp(sfail, dpfail, dppass);
		}
		inline static void EnableCullFace(bool enabled)
		{
			s_RnedererAPI->EnableCullFace(enabled);
		}
		inline static void CullFace(CullFaceOption option)
		{
			s_RnedererAPI->CullFace(option);
		}
		inline static void BindTexture(uint32_t texture, uint32_t slot)
		{
			s_RnedererAPI->BindTexture(texture,slot);
		}
	private:
		 static RendererAPI* s_RnedererAPI;
	};

}