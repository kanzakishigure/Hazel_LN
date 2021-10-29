#include<Hazel.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi

glm::mat4 camera(float Translate, glm::vec2 const& Rotate)
{
	glm::mat4 Projection = glm::perspective(glm::pi<float>() * 0.25f, 4.0f / 3.0f, 0.1f, 100.f);
	glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
	View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
	View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	return Projection * View * Model;
}

class ExampleLayer : public Hazel::Layer
{
public:
	ExampleLayer()
		:Layer("ExampleLayer"){}
	void OnUpdate() override
	{
		if (Hazel::Input::IsKeyPressed(HZ_KEY_O))
			HZ_TRACE("0 is pressed");
		auto cam = camera(1.0f, { 5.0f,1.2f });

	}
	void OnEvent(Hazel::Event& e) override
	{
		if (e.GetEventType() == Hazel::EventType::KeyPressed)
		{
			Hazel::KeyPressEvent& E = (Hazel::KeyPressEvent&)e;
			HZ_WARN("{0} is pressed,eventpoll",(char)E.GetKeyCode());
		}
			
		//HZ_INFO("ExampleLayer Event:{0}",e);
	}
	
private:

};

class SandBox : public Hazel::Application
{
public :

	SandBox()
	{
		PushLayer(new ExampleLayer());
		PushLayer(new Hazel::ImGuiLayer());
	}
	~SandBox()
	{

	}
	
};
Hazel::Application* Hazel::createApplication()
{
	return new SandBox();
}