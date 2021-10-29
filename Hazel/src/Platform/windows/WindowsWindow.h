#pragma once
#include"Hazel/Window.h"
#include<GLFW/glfw3.h>

namespace Hazel {
	class HAZEL_API WindowsWindow : public Window
	{
	public:
		
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();
		void OnUpdate() override;
		inline unsigned int GetWidth() const override		{ return m_Data.Width; }
		inline unsigned int GetHeight() const override		{ return m_Data.Height; }

		//�ṹ
		inline void SetEventCallback(const EventCallbackFn& callback) override     { m_Data.EventCallback = callback; }
		void SeyVSync(bool enable) override;
		bool IsVSync() const override ;
		virtual inline void* GetNativeWindow() const override { return m_Window; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown ();

	private:
		GLFWwindow* m_Window;
		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};
		//ͨ���ṹ��������ȫ������

		WindowData m_Data;
	};
}