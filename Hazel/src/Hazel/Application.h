#pragma once
#include"Core/Core.h"
#include"Events/Event.h"
#include"Window.h"
namespace Hazel{


	class HAZEL_API Application
	{
		public:
			Application();
			virtual ~Application();//该类会在sandbox内形成子类，固作虚函数。方便在继承的子类内进行实现

			void run();
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running ;
	};

	Application* createApplication();//该函数只应在应用端实现


}

