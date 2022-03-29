#pragma once
#include "RendererAPI.h"
namespace Hazel {

	class RenderCommand
	{
	public:
		//RenderCommand�ڲ�Ӧ�����㵥һְ��ԭ�򣬲�Ӧ��ʵ�ֶ���Ĺ��ܣ����¹�ź��
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
	private:
		 static RendererAPI* s_RnedererAPI;
	};

}