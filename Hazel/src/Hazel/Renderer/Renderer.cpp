#include "hzpch.h"
#include "Renderer.h"
#include "Renderer2D.h"
#include "Platform/OpenGL/OpenGLShader.h"
namespace Hazel {
	
	Renderer::RendererData* Renderer::m_RendererData = new RendererData;

	void Renderer::Init()
	{
		HZ_PROFILE_FUCTION();
		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::BeginScene(const OrthographicCamera& camera)
	{
		m_RendererData->ViewProjectionMatix = camera.GetViewProjectionMatrtix();
		//׼��camera��texture,���ʣ����յȵ������������Ϣ
	}


	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const Ref<Shader>& shader,const Ref<VertexArray>& vertexArray,const glm::mat4& transform)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("U_ViewProjection", m_RendererData->ViewProjectionMatix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("U_Transform", transform);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewPort(0, 0, width, height);
	}

}