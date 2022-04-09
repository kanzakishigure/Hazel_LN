#include <Hazel.h>
#include <Hazel/Core/EntryPoint.h>

#include "Platform/OpenGL/OpenGLShader.h"
#include "Hazel/Renderer/Shader.h"

#include <imgui.h>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Sandbox2D.h"
class ExampleLayer : public Hazel::Layer
{
public:
	ExampleLayer()
		:Layer("ExampleLayer"),m_CameraController(1920.0f/1080.0f)
	{
		//vertex array
		m_VertexArray = Hazel::VertexArray::Create();
		//vertex buffer
		float vertex[3 * 7]{
		   -0.5f,-0.5f,0.0f, 1.0f,0.8f,0.6f,1.0f,
			0.5f,-0.5f,0.0f, 1.0f,0.8f,0.6f,1.0f,
			0.0f,0.5f,0.0f , 1.0f,0.8f,0.6f,1.0f
		};
		Hazel::Ref<Hazel::VertexBuffer> vertexBuffer(Hazel::VertexBuffer::Create(vertex, sizeof(vertex)));
		vertexBuffer->Bind();

		{

			Hazel::BufferLayout layout = {
				//{ShaderDataType::Int2,"UVcrooods"},
				{Hazel::ShaderDataType::Float3,"GLposition"},
				{Hazel::ShaderDataType::Float4,"GLcolar"}
			};
			vertexBuffer->SetBufferLayout(layout);
		}
		//index buffer
		uint32_t index[3]{ 0,1,2 };
		//显视调用构造函数进行初始化操作
		Hazel::Ref<Hazel::IndexBuffer> indexBuffer(Hazel::IndexBuffer::Create(index, sizeof(index)));

		indexBuffer = Hazel::IndexBuffer::Create(index, sizeof(index) / sizeof(uint32_t));
		indexBuffer->Bind();
		//VertexArray
		m_VertexArray->AddVertexBuffer(vertexBuffer);
		m_VertexArray->SetIndexBuffer(indexBuffer);
		//Shader Program

		std::string vertexlocation;
		vertexlocation = "F:/EngineLearning/Hazel/Hazel/shadersrc/vertexshader/vertexshader.vs";
		std::string fragmentlocation;
		fragmentlocation = "F:/EngineLearning/Hazel/Hazel/shadersrc/fragmentshader/fragmentshader.fs";
		shaderLibrary.Add(Hazel::Shader::Create("vertex tangle shader", vertexlocation, fragmentlocation));
		m_Shader = shaderLibrary.Get("vertex tangle shader");
		
			float vertex2[]{
			   -0.5f,-0.5f,0.0f,0.0f,0.0f,
				0.5f,-0.5f,0.0f,1.0f,0.0f,
				0.5f, 0.5f,0.0f,1.0f,1.0f,
				-0.5f,0.5f,0.0f,0.0f,1.0f
		};
		uint32_t index2[]{ 0,1,2,0,2,3 };
		
		Hazel::Ref<Hazel::VertexBuffer> BlueVertexBuffer(Hazel::VertexBuffer::Create(vertex2, sizeof(vertex2)));
		Hazel::Ref<Hazel::IndexBuffer> BlueindexBuffer(Hazel::IndexBuffer::Create(index2, sizeof(index2)));
		BlueVertexBuffer->SetBufferLayout(
			{
			 { Hazel::ShaderDataType::Float3,"GLposition" },
			 {Hazel::ShaderDataType::Float2,"GLtexturecroods"}
			}
		);
		std::string blueshaderpath;
		blueshaderpath = "assets/shaders/Blue.glsl";
		BlueShadervertexArray = Hazel::VertexArray::Create();
		BlueShadervertexArray->AddVertexBuffer(BlueVertexBuffer);
		BlueShadervertexArray->SetIndexBuffer(BlueindexBuffer);

		BlueShadershader = Hazel::Shader::Create(blueshaderpath);

		chessbord = Hazel::Texture2D::Create("assets/textures/Checkerboard.png");
		icon = Hazel::Texture2D::Create("assets/textures/ChernoLogo.png");
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(BlueShadershader)->Bind();
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(BlueShadershader)->UploadUniformInt("U_Texture",0);
		
	}
	virtual void OnUpdate(Hazel::TimeStep ts) override
	{
		//m_Framebuffer->Bind();
		m_CameraController.OnUpdate(ts);

		
		
		bluetransform = glm::translate(glm::mat4(1.0), glm::vec3(0.0, 0.0, 0.0));
		transform = glm::translate(glm::mat4(1.0), Tsform);
		
		Hazel::RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1.0f });
		Hazel::RenderCommand::Clear();

		bluetransform = glm::scale(bluetransform, glm::vec3(0.1, 0.1, 0.1));
		//Hazel::Renderer::BeginScene(m_CameraController.GetOrthographicCamera());
		for (uint32_t i = 0; i < 20; i++)
		{
			for (uint32_t j = 0;j < 20; j++)
			{
				bluetransform = glm::translate(glm::mat4(1.0), glm::vec3( i*0.1, j*0.1, 0.0));
				bluetransform = glm::scale(bluetransform, glm::vec3(0.1, 0.1, 0.1));
				std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_Shader)->UploadUniform3Float("U_Color", bluecolor);
				Hazel::Renderer::Submit(m_Shader, BlueShadervertexArray, bluetransform);
			}
		}
		chessbord->Bind();
		Hazel::Renderer::Submit(BlueShadershader, BlueShadervertexArray, glm::scale(glm::mat4(1.0), glm::vec3(1, 1, 1)));
		icon->Bind();
		Hazel::Renderer::Submit(BlueShadershader, BlueShadervertexArray, glm::scale(glm::mat4(1.0), glm::vec3(1, 1, 1)));
		
		//Hazel::Renderer::Submit(m_Shader, m_VertexArray,transform);
		
		Hazel::Renderer::EndScene();
		//m_Framebuffer->Unbind();
	}
	void OnEvent(Hazel::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}
	void OnImGuiRender() override
	{
		m_Framebuffer->Bind();
		ImGui::Begin("setting");
		ImGui::ColorEdit3("squar_color", glm::value_ptr(bluecolor));
		uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
		ImGui::Image((void*)textureID, ImVec2{ 330, 330 });
		ImGui::End();
		m_Framebuffer->Unbind();
	}
	void OnAttach() 
	{
		HZ_INFO("layer attach!");
		Hazel::FrameBufferSpecification spec;
		spec.Height = 1080;
		spec.Width = 1920;

		m_Framebuffer = Hazel::FrameBuffer::Create(spec);

	}
	
private:
	Hazel::Ref<Hazel::Shader> m_Shader;
	Hazel::Ref<Hazel::VertexArray> m_VertexArray;
	glm::mat4 transform;

	Hazel::Ref<Hazel::Shader> BlueShadershader;
	Hazel::Ref<Hazel::VertexArray> BlueShadervertexArray;
	glm::mat4 bluetransform;
	
	//TODO
	//该项应该静态化，从而实现Rnederer::shaderlibrary的方式实现shader的load，add,get
	Hazel::ShaderLibrary shaderLibrary;

	Hazel::Ref<Hazel::Texture> chessbord;
	Hazel::Ref<Hazel::Texture> icon;
	

	glm::vec3 bluecolor={1.0,1.0,1.0};
	glm::vec3 Tsform = glm::vec3(0.0);


	Hazel::Ref<Hazel::FrameBuffer> m_Framebuffer;

	Hazel::OrthographicCameraController m_CameraController;
	
};

class SandBox : public Hazel::Application
{
public :

	SandBox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2DLayer());
	}
	~SandBox()
	{

	}
	
};
Hazel::Application* Hazel::createApplication()
{
	return new SandBox();
}