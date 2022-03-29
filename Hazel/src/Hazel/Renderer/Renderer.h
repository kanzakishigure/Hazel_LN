#pragma once
#include "RenderCommand.h"
#include "Hazel/Renderer/OrthographicCamera.h"
#include "Shader.h"
namespace Hazel {
	
	class Renderer
	{
	public:
		
		static void	Init();
		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();
		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform);
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