#pragma once
#ifdef  HZ_PLATFORM_WINDOWS

extern Hazel::Application* Hazel::createApplication();
//因为我们不知道实际的应用类型，所以我们定义一个能返回类指针的函数，并在其他地方实现它，在此引擎的情况下，我们会在用户端将其实例化

int main(int argc,char** argv)
{
	Hazel::Log::Init();
	HZ_CORE_WARN("初始化日志系统");
	HZ_INFO("welcome");

	/*
	HZ_CORE_ERROR("HZ_CORE_ERROR");
	HZ_ERROR("HZ_ERROR");
	*/
	
	auto app = Hazel::createApplication();

	//谨慎使用void*和this指针，以及认识到构造函数编写的严谨性
	//auto x = app->getthisPoint();

	app->run();
	
	delete app;
}

#endif //  HZ_PLATFORM_WINDOWS