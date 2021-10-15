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

		HZ_CORE_INFO("��������{0}({1},{2})", props.Title, props.Width, props.Height);
		if (!s_GLiFWIntialized)
		{
			//TODO��glfwterminate on system shutdown
			int success = glfwInit();
			HZ_CORE_ASSERT(success, "�޷���ʼ��GLFW!");
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
		//����Ƿ����¼������������¼�����������״̬�����ø��¼��Ļص�����
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
		//(����һ��������GLFW����ÿһ��������ɫֵ�Ĵ󻺳壩��������һ�����б��������ƣ����ҽ�����Ϊ�����ʾ����Ļ�ϡ�
	}
	void WindowsWindow::SeyVSync(bool enable)
	{
		//�����첽
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