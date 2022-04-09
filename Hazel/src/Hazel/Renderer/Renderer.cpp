#include "hzpch.h"
#include "Renderer.h"
#include "Renderer2D.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Hazel/Renderer/SceneCamera.h"
namespace Hazel {
	
	Renderer::RendererData* Renderer::m_RendererData = new RendererData;

	void Renderer::Init()
	{
		HZ_PROFILE_FUCTION();
		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::BeginScene(const Camera& camera, const glm::mat4& transform)
	{
		
		m_RendererData->ViewProjectionMatix = camera.GetProjectMatrix()*glm::inverse(transform);
		//准备camera，texture,材质，光照等等所有所需的信息
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

	void Renderer::Submit(const Ref<Material>& material, const Ref<MeshSource>& mesh, const glm::mat4& transform)
	{
		
		auto& shader = material->GetShader();
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("U_ViewProjection", m_RendererData->ViewProjectionMatix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("U_Transform", transform);
		
		auto& vaos = mesh->GetVertexArray();
		
		for (auto& VA :vaos)
		{

			VA->Bind();
			RenderCommand::DrawIndexed(VA);
		}
		
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewPort(0, 0, width, height);
	}

}