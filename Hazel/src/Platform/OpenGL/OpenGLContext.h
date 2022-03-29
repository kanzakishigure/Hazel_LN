#pragma once
#include "Hazel/Renderer/GraphicContext.h"

struct GLFWwindow;
namespace Hazel {

	class OpenGLContext :public GraphicContext
	{
	public:
		virtual void Init() override;
		virtual void SwapBuffers() override;
		OpenGLContext(GLFWwindow* windowHandle);

	private:
		GLFWwindow* m_WindowHandle;
		
	};

}
