#include"hzpch.h"
#include"Platform/windows/WindowsWindow.h"
#include"Platform/OpenGL/OpenGLContext.h"

#include"Hazel/Events/ApplicationEvent.h"
#include"Hazel/Events/KeyEvent.h"
#include"Hazel/Events/MouseEvent.h"

#include<glad/glad.h>

namespace Hazel {

	static bool s_GLiFWIntialized = false;
	int WindowsWindow::s_GLFWWindowsCount = 0;

	static void GLFWErrorCallback(int error,const char* description)
	{
		HZ_CORE_ERROR("GLFW Error ({0}):{1}", error, description);
	}
	Scope<Window> Window::Create(const WindowProps& props)
	{
		return CreateScope<WindowsWindow>(props);
		
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
		HZ_PROFILE_FUCTION();
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		HZ_CORE_INFO("��������{0}({1},{2})", props.Title, props.Width, props.Height);
		if (!s_GLiFWIntialized)
		{
			//TODO��glfwterminate on system shutdown
			HZ_PROFILE_SCOPE("glfwInit");

			int success = glfwInit();
			HZ_CORE_ASSERT(success, "�޷���ʼ��GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLiFWIntialized = true;
		}
		{
			HZ_PROFILE_SCOPE("glfwCreateWindow");
			m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), NULL, NULL);
			s_GLFWWindowsCount++;			

		}
		
		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();
		
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
		//���ô��ڻص�����
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window,int width,int height) 
			{

				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Height = height;
				data.Width = width;
				
				WindowResizeEvent event(width,height);
				data.EventCallback(event);
				
			});
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.EventCallback(event);
			});
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				switch (action)
				{
					case GLFW_PRESS:
					{
						WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
						KeyPressedEvent event(key,0);
						data.EventCallback(event);
					}
						break;
					case GLFW_REPEAT:
					{
						WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
						KeyPressedEvent event(key, 1);
						data.EventCallback(event);
					}
						break;
					case GLFW_RELEASE:
					{
						WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
						KeyReleasedEvent event(key);
						data.EventCallback(event);
					}
						break;
				}
			});
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window,int button,int action,int mods) 
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				switch (action)
				{
					case GLFW_PRESS:
						{
							WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
							MouseButtonPressedEvent event(button);
							data.EventCallback(event);
						}
						break;
					case GLFW_RELEASE:
						{
							WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
							MouseButtonReleasedEvent event(button);
							data.EventCallback(event);
						}
							break;
				}
				
			
			});
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window,double xoffset,double yoffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent event((float)xoffset, (float)yoffset);
			data.EventCallback(event);
			});
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMoveEvent event((float)xpos, (float)ypos);
			data.EventCallback(event);
			});
		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent event(keycode);
			data.EventCallback(event);
			});
		
	}
	void WindowsWindow::Shutdown()
	{
		HZ_PROFILE_FUCTION();
		//GLFWapi
		glfwDestroyWindow(m_Window);
		
	}
	void WindowsWindow::OnUpdate()
	{
		HZ_PROFILE_FUCTION();
		//����Ƿ����¼������������¼�����������״̬�����ø��¼��Ļص�����
		glfwPollEvents();
		m_Context->SwapBuffers();
		//(����һ��������GLFW����ÿһ��������ɫֵ�Ĵ󻺳壩��������һ�����б��������ƣ����ҽ�����Ϊ�����ʾ����Ļ�ϡ�
	}
	void WindowsWindow::SetVSync(bool enable)
	{
		HZ_PROFILE_FUCTION();
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