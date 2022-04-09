#pragma once
#include "RenderCommand.h"
#include "Hazel/Renderer/OrthographicCamera.h"
#include "Shader.h"
#include "Hazel/Renderer/Material.h"
#include "Hazel/Renderer/Mesh.h"
#include "Hazel/Renderer/Camera.h"
namespace Hazel {
	
	class Renderer
	{
	public:
		
		static void	Init();
		static void BeginScene(const Camera& camera, const glm::mat4& transform);
		static void EndScene();
		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform);
		static void Submit(const Ref<Material>& material, const Ref<MeshSource>& mesh, const glm::mat4& transform);
		static void OnWindowResize(uint32_t width, uint32_t height);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct RendererData
		{
			glm::mat4 ViewProjectionMatix;
		};

		static RendererData* m_RendererData;
	};
	
}