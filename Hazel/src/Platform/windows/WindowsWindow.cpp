#include"hzpch.h"
#include"Platform/windows/WindowsWindow.h"

namespace Hazel {

	static bool s_GLiFWIntialized = false;

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}
	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		WindowsWindow::Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		HZ_CORE_INFO("创建窗口{0}({1},{2})", props.Title, props.Width, props.Height);
		if (!s_GLiFWIntialized)
		{
			//TODO：glfwterminate on system shutdown
			int success = glfwInit();
			HZ_CORE_ASSERT(success, "无法初始化GLFW!");
			s_GLiFWIntialized = true;
		}
		m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(),nullptr,nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SeyVSync(true);
	}
	void WindowsWindow::Shutdown()
	{
		//GLFWapi
		glfwDestroyWindow(m_Window);
		
	}
	void WindowsWindow::OnUpdate()
	{
		//检测是否有事件触发，若有事件触发，更新状态，调用该事件的回调函数
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
		//(它是一个储存着GLFW窗口每一个像素颜色值的大缓冲），它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上。
	}
	void WindowsWindow::SeyVSync(bool enable)
	{
		//启动异步
		if (enable)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enable;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
	
}