#pragma once
#include "RenderCommand.h"
#include "Hazel/Renderer/OrthographicCamera.h"
#include "Hazel/Renderer/Shader.h"
#include "Hazel/Renderer/Mesh.h"
#include "Hazel/Renderer/Camera.h"
//test
#include "Hazel/Scene/Scene.h"
namespace Hazel {
	

	class Renderer
	{
	public:
		
		static void	Init();
		static void RendererDataInit();
		static void BeginScene(const Camera& camera, const glm::mat4& transform);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform);
		static void OnWindowResize(uint32_t width, uint32_t height);

		static Ref<Texture2D> GetWhiteTexture();
		static Ref<Texture2D> GetBlackTexture();
		static Ref<ShaderLibrary> GetShaderLibrary();

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct RendererData
		{
			glm::mat4 ViewProjectionMatix;
	
			Ref<Texture2D> WhiteTexture;
			Ref<Texture2D> BlackTexture;
			Ref<ShaderLibrary> m_ShaderLibrary;
		};

		static RendererData* s_RendererData;
	};
	
}