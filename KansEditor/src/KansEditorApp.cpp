#include <Hazel.h>
#include <Hazel/Core/EntryPoint.h>

#include "Platform/OpenGL/OpenGLShader.h"
#include "Hazel/Renderer/Shader.h"

#include <imgui.h>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "EditorLayer.h"

namespace Hazel {

	class KansEditor : public Hazel::Application
	{
	public:

		KansEditor()
		{
			//PushLayer(new ExampleLayer());
			PushLayer(new EditorLayer());
		}
		~KansEditor()
		{

		}

	};
	Hazel::Application* Hazel::createApplication()
	{
		return new KansEditor();
	}


}
