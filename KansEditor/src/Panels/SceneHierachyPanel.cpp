#include "SceneHierachyPanel.h"
#include "Hazel/Scene/Components.h"
#include "Hazel/Scene/Entity.h"
namespace Hazel
{

	SceneHierachyPanel::SceneHierachyPanel(const Ref<Scene>& scene)
	{
		SetContext(scene);
	}

	void SceneHierachyPanel::SetContext(const Ref<Scene>& context)
	{
		m_Context = context;
	}

	void SceneHierachyPanel::OnImguiRender()
	{
		ImGui::Begin("SceneHierachyPanel:");

		m_Context->m_Rehistry.each([&](auto entityID) {
			Entity entity = { entityID ,m_Context.get() };
			auto tc = entity.GetComponent<TagComponent>();
			ImGui::Text(" %s ", tc.Tag.c_str());
			});
		ImGui::End();
	}

}

