#include "hzpch.h"
#include "WindowsInput.h"

#include "Hazel/Application.h"
#include <GLFW/glfw3.h>
namespace Hazel{
	
	Input* Input::s_Instance = new WindowsInput();
	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto Window =static_cast<GLFWwindow*>( Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(Window, keycode);
		return state == GLFW_PRESS||state==GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto Window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(Window, button);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}


	float WindowsInput::GetMouseXImpl()
	{
		auto [X, Y] = GetMousePositionImpl();
		return (float)X;
	}
	float WindowsInput::GetMouseYImpl()
	{
		auto [X, Y] = GetMousePositionImpl();
		return (float)Y;
	}
	//c++17新特性std::pair 返回一对数值，使用{}
	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		auto Window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double Xpos, Ypos;
		glfwGetCursorPos(Window, &Xpos, &Ypos);
		return {(float)Xpos,(float)Ypos};
	}

}