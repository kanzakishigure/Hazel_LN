#pragma once
#include <glm/glm.hpp>
#include "Hazel/Renderer/Mesh.h"
#include "Hazel/Renderer/SceneCamera.h"
#include "Hazel/Scene/Scene.h"
namespace Hazel
{
	struct SceneRendererCamera
	{
		SceneCamera camera;
		glm::mat4 viewMatrix;
		glm::vec3 Position;
	};
	struct SceneInfo
	{
		DirLight dirLight;
		PointLight pointLight;
		SceneRendererCamera sceneCamera;
	};
	
	class Scene;
	class SceneRenderer 
	{
		public:
			SceneRenderer(Ref<Scene> scene);
			~SceneRenderer(){};

			void Init();
			void BeginScene(SceneInfo info);
			void EndScene();
			void SetScene(Ref<Scene> scene) { m_Scene = scene; }
			void SubmitStaticMesh(Ref<StaticMesh> mesh,Ref<MaterialTable> material,glm::mat4 transform);
			
		private:
			//SceneRenderer did't handle the life of Scnene;
			Ref<Scene> m_Scene;
			SceneInfo m_SceneInfo;
			bool m_Active = false;
	};
}