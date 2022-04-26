#include "hzpch.h"
#include "Hazel/Renderer/SceneRenderer.h"
#include "Hazel/Renderer/Renderer.h"
namespace Hazel 
{

	SceneRenderer::SceneRenderer(Ref<Scene> scene)
		:m_Scene(scene)
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

}