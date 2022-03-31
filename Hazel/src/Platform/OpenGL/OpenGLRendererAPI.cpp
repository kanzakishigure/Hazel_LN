#include "hzpch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>
namespace Hazel {

	void OpenGLRendererAPI::Init()
	{
		HZ_PROFILE_FUCTION();
		//����������Ⱦ��������ܼ�⣬��ʹ��HZ_PROFILE_FUNCTION�������ļ�⣬��Ϊÿ����Ⱦִ�е�ʱ�򶼻���д����ĸ��Ӳ�������ִ��ÿ�������ʱ�򣬻����Ĵ�����ʱ�䣬�Լ��ڴ濪��
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
		

	}
	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.b, color.g, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	}


	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount /*= 0*/)
	{
		uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRendererAPI::SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

}