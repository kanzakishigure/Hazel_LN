#pragma once
#ifdef  HZ_PLATFORM_WINDOWS

extern Hazel::Application* Hazel::createApplication();
//��Ϊ���ǲ�֪��ʵ�ʵ�Ӧ�����ͣ��������Ƕ���һ���ܷ�����ָ��ĺ��������������ط�ʵ�������ڴ����������£����ǻ����û��˽���ʵ����

int main(int argc,char** argv)
{
	Hazel::Log::Init();
	HZ_CORE_WARN("��ʼ����־ϵͳ");
	HZ_INFO("welcome");

	/*
	HZ_CORE_ERROR("HZ_CORE_ERROR");
	HZ_ERROR("HZ_ERROR");
	*/
	auto app = Hazel::createApplication();
	app->run();
	delete app;
}

#endif //  HZ_PLATFORM_WINDOWS