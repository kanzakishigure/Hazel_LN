#include "hzpch.h"
#include "Renderer.h"
#include "Renderer2D.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Hazel/Renderer/SceneCamera.h"
namespace Hazel {
	
	Renderer::RendererData* Renderer::s_RendererData = new Renderer::RendererData;

	void Renderer::Init()
	{
		HZ_PROFILE_FUCTION();
		
		Renderer::RendererDataInit();

		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::RendererDataInit()
	{
		//init renderer asset
		//Texture
		{
			s_RendererData->WhiteTexture = Texture2D::Create(1, 1);
			uint32_t data = 0xffffffff;
			s_RendererData->WhiteTexture->SetData((void*)&data, sizeof(uint32_t));

			s_RendererData->BlackTexture = Texture2D::Create(1, 1);
			data = 0xff000000;
			s_RendererData->BlackTexture->SetData((void*)&data, sizeof(uint32_t));
		}
		//shader
		{
			s_RendererData->m_ShaderLibrary = CreateRef<ShaderLibrary>();
			auto StaticShader = Shader::Create("F:/Kans3D/Hazel/KansEditor/assets/shaders/StaticMeshShader.glsl");
			StaticShader->SetShaderBuffer({
					{ShaderDataType::Float3,"U_Diffuse"},
					{ShaderDataType::Float3,"U_Specular"},
					{ShaderDataType::Float3,"U_Emission"},
					{ShaderDataType::Float,"U_Shininess"},
				});
			s_RendererData->m_ShaderLibrary->Add(StaticShader);
		}

	}

	void Renderer::BeginScene(const Camera& camera, const glm::mat4& transform)
	{
		
		s_RendererData->ViewProjectionMatix = camera.GetProjectMatrix()*glm::inverse(transform);
		//准备camera，texture,材质，光照等等所有所需的信息
	}


	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const Ref<Shader>& shader,const Ref<VertexArray>& vertexArray,const glm::mat4& transform)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("U_ViewProjection", s_RendererData->ViewProjectionMatix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("U_Transform", transform);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

	void Renderer::Submit(const Ref<StaticMesh> mesh, const glm::mat4& transform)
	{
		auto& VAOs = mesh->GetMeshSource()->GetVertexArray();
		auto& shader = mesh->GetMeshSource()->GetMeshShader();
		shader->Bind();
		Ref<MaterialTable>& materialTable = mesh->GetMaterials();
		
		shader->SetMat4("U_ViewProjection", s_RendererData->ViewProjectionMatix);
		shader->SetMat4("U_Transform", transform);
		for (auto& mesh : mesh->GetSubMesh())
		{
			auto VA = VAOs[mesh];
			VA->Bind();
			auto subMtl =  materialTable->GetMaterialAsset(mesh)->GetMaterial();
			subMtl->Invalidate();
			RenderCommand::DrawIndexed(VA);
		}
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewPort(0, 0, width, height);
	}

	Ref<Texture2D> Renderer::GetWhiteTexture()
	{
		return s_RendererData->WhiteTexture;
	}

	Ref<Texture2D> Renderer::GetBlackTexture()
	{
		return s_RendererData->BlackTexture;
	}

	Ref<ShaderLibrary> Renderer::GetShaderLibrary()
	{
		return s_RendererData->m_ShaderLibrary;
	}


}