#include "hzpch.h"
#include "Hazel/Renderer/SceneRenderer.h"
#include "Hazel/Renderer/Renderer.h"
//test
#include "imgui.h"
namespace Hazel 
{

	SceneRenderer::SceneRenderer(Ref<Scene> scene, SceneRendererSpecification spec)
		:m_Scene(scene),m_Specification(spec)
	{
		Init();
	}

	void SceneRenderer::Init()
	{
		//Init the shader 
		//Set the shader buffer
	}

	void SceneRenderer::BeginScene(SceneInfo info)
	{
		m_Active = true;
		m_SceneInfo = info;
	}

	void SceneRenderer::EndScene()
	{
		m_Active = false;
	}

	void SceneRenderer::SetScene(Ref<Scene> scene)
	{
		HZ_ASSERT(scene, "Handel a nullptr scene");
		m_Scene = scene;
	}

	void SceneRenderer::SubmitStaticMesh(Ref<StaticMesh> mesh, Ref<MaterialTable> material, glm::mat4 transform)
	{
		auto& VAOs = mesh->GetMeshSource()->GetVertexArray();
		auto& shader = mesh->GetMeshSource()->GetMeshShader();
		shader->Bind();

		glm::mat4 viewprojection = m_SceneInfo.sceneCamera.camera.GetProjectMatrix()*m_SceneInfo.sceneCamera.viewMatrix;
		shader->SetMat4("U_ViewProjection", viewprojection);
		shader->SetMat4("U_Transform", transform);
		for (auto& mesh : mesh->GetSubMesh())
		{
			auto VA = VAOs[mesh];
			VA->Bind();
			auto subMtl = material->GetMaterialAsset(mesh)->GetMaterial();

			//SetLight
			{
				//Dir
				subMtl->Set("dirLight.LightDir", m_SceneInfo.dirLight.Dirction);
				subMtl->Set("dirLight.Ambient_Intensity", m_SceneInfo.dirLight.Ambient_Intensity);
				subMtl->Set("dirLight.Diffuse_Intensity", m_SceneInfo.dirLight.Diffuse_Intensity);
				subMtl->Set("dirLight.Specular_Intensity", m_SceneInfo.dirLight.Specular_Intensity);

				//Point
				subMtl->Set("pointLight.Position", m_SceneInfo.pointLight.Position);
				subMtl->Set("pointLight.Ambient_Intensity", m_SceneInfo.pointLight.Ambient_Intensity);
				subMtl->Set("pointLight.Diffuse_Intensity", m_SceneInfo.pointLight.Diffuse_Intensity);
				subMtl->Set("pointLight.Specular_Intensity", m_SceneInfo.pointLight.Specular_Intensity);
			}
			//SetScene
			{
				subMtl->Set("U_ViewPos", m_SceneInfo.sceneCamera.Position);
			}


			subMtl->Invalidate();
			RenderCommand::DrawIndexed(VA);
		}
	}

	void SceneRenderer::SubmitStaticMeshStencil(Ref<StaticMesh> mesh, glm::mat4 transform)
	{
		auto& VAOs = mesh->GetMeshSource()->GetVertexArray();
		auto& shader = Renderer::GetShaderLibrary()->Get("StencilShader");
		shader->Bind();
		glm::mat4 viewprojection = m_SceneInfo.sceneCamera.camera.GetProjectMatrix() * m_SceneInfo.sceneCamera.viewMatrix;
		shader->SetMat4("U_ViewProjection", viewprojection);
		shader->SetMat4("U_Transform", transform);

		for (auto& mesh : mesh->GetSubMesh())
		{
			auto VA = VAOs[mesh];
			VA->Bind();
			RenderCommand::DrawIndexed(VA);
		}
	}

	void SceneRenderer::SubmitStaticMeshPostEffect(Ref<StaticMesh> mesh, Ref<Texture2D> attachment, glm::mat4 transform)
	{
		auto& VAOs = mesh->GetMeshSource()->GetVertexArray();
		auto& shader = Renderer::GetShaderLibrary()->Get("PostShader");
		shader->Bind();
		glm::mat4 viewprojection = m_SceneInfo.sceneCamera.camera.GetProjectMatrix() * m_SceneInfo.sceneCamera.viewMatrix;
		shader->SetMat4("U_ViewProjection", viewprojection);
		shader->SetMat4("U_Transform", transform);
		attachment->Bind();
		for (auto& mesh : mesh->GetSubMesh())
		{
			auto VA = VAOs[mesh];
			VA->Bind();
			RenderCommand::DrawIndexed(VA);
		}
	}

	void SceneRenderer::SubmitStaticMeshOutLine(Ref<StaticMesh> mesh, glm::mat4 transform)
	{
		auto& VAOs = mesh->GetMeshSource()->GetVertexArray();
		auto& shader = Renderer::GetShaderLibrary()->Get("OutLineShader");
		shader->Bind();
		glm::mat4 viewprojection = m_SceneInfo.sceneCamera.camera.GetProjectMatrix() * m_SceneInfo.sceneCamera.viewMatrix;
		shader->SetMat4("U_ViewProjection", viewprojection);
		shader->SetMat4("U_Transform", transform);


		for (auto& mesh : mesh->GetSubMesh())
		{
			auto& VA = VAOs[mesh];
			VA->Bind();
			RenderCommand::DrawIndexed(VA);
		}

	}

	void SceneRenderer::SubmitStaticMeshToneshading(Ref<StaticMesh> mesh, Ref<MaterialTable> material, glm::mat4 transform, ToneShaderData data)
	{
		auto& VAOs = mesh->GetMeshSource()->GetVertexArray();	
		auto& shader = Renderer::GetShaderLibrary()->Get("ToneShader");
		shader->Bind();

		glm::mat4 viewprojection = m_SceneInfo.sceneCamera.camera.GetProjectMatrix() * m_SceneInfo.sceneCamera.viewMatrix;
		shader->SetMat4("U_ViewProjection", viewprojection);
		shader->SetMat4("U_Transform", transform);
		uint32_t meshs[5] = { 0,1,3,2,4 };
		for (auto& mesh : meshs)
		{
			auto VA = VAOs[mesh];
			VA->Bind();
			auto subMtl = material->GetMaterialAsset(mesh)->GetMaterial();

			//SetLight
			{
				//Dir
				shader->SetFloat3("dirLight.LightDir", m_SceneInfo.dirLight.Dirction);
				shader->SetFloat3("dirLight.Ambient_Intensity", m_SceneInfo.dirLight.Ambient_Intensity);
				shader->SetFloat3("dirLight.Diffuse_Intensity", m_SceneInfo.dirLight.Diffuse_Intensity);
				shader->SetFloat3("dirLight.Specular_Intensity", m_SceneInfo.dirLight.Specular_Intensity);

				//Point
				shader->SetFloat3("pointLight.Position", m_SceneInfo.pointLight.Position);
				shader->SetFloat3("pointLight.Ambient_Intensity", m_SceneInfo.pointLight.Ambient_Intensity);
				shader->SetFloat3("pointLight.Diffuse_Intensity", m_SceneInfo.pointLight.Diffuse_Intensity);
				shader->SetFloat3("pointLight.Specular_Intensity", m_SceneInfo.pointLight.Specular_Intensity);
			}
			//SetScene
			{
				subMtl->Set("U_ViewPos", m_SceneInfo.sceneCamera.Position);
				shader->SetFloat("U_BoundSharp", data.BoundSharp);

				shader->SetFloat("U_DividLineH", data.DividLineH);
				shader->SetFloat("U_DividLineM", data.DividLineM);
				shader->SetFloat("U_DividLineL", data.DividLineL);

				shader->SetFloat4("U_DarkColor", data.DarkColor);
			}


			subMtl->Invalidate();
			RenderCommand::DrawIndexed(VA);
		}
	}

}