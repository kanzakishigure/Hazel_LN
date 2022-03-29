#pragma once
#include "Hazel/Core/Core.h"
#ifdef  HZ_PLATFORM_WINDOWS

extern Hazel::Application* Hazel::createApplication();
//��Ϊ���ǲ�֪��ʵ�ʵ�Ӧ�����ͣ��������Ƕ���һ���ܷ�����ָ��ĺ��������������ط�ʵ�������ڴ����������£����ǻ����û��˽���ʵ����

int main(int argc,char** argv)
{
	Hazel::Log::Init();

	HZ_PROFILE_BEGIN_SESSION("startup","startup-profile.json");
	auto app = Hazel::createApplication();
	HZ_PROFILE_END_SESSION();

	//����ʹ��void*��thisָ�룬�Լ���ʶ�����캯����д���Ͻ���
	//auto x = app->getthisPoint();
	HZ_PROFILE_BEGIN_SESSION("runtime", "runtime-profile.json");
	app->run();
	HZ_PROFILE_END_SESSION();

	HZ_PROFILE_BEGIN_SESSION("shutdown", "shutdown-profile.json");
	delete app;
	HZ_PROFILE_END_SESSION();
}

#endif //  HZ_PLATFORM_WINDOWS