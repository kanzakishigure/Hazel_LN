#pragma once
#include <imgui.h>
#include "Hazel/Core/Base.h"
#include "Hazel/Core/Log.h"
#include "Hazel/Scene/Scene.h"
namespace Hazel
{


	class SceneHierachyPanel {

	public: 
		SceneHierachyPanel() = default;
		SceneHierachyPanel(const Ref<Scene>& scene);
		void SetContext(const Ref<Scene>& context);
		void OnImguiRender();
	private:
		Ref<Scene> m_Context = nullptr;

		
	};
}