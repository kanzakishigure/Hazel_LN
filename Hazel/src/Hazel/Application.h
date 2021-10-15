#pragma once
#include"Core/Core.h"
#include"Events/Event.h"
#include"Window.h"
namespace Hazel{


	class HAZEL_API Application
	{
		public:
			Application();
			virtual ~Application();//�������sandbox���γ����࣬�����麯���������ڼ̳е������ڽ���ʵ��

			void run();
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running ;
	};

	Application* createApplication();//�ú���ֻӦ��Ӧ�ö�ʵ��


}

