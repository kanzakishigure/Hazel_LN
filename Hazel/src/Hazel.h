#pragma once
//此头文件只向外开放(应用程序)，Hazel引擎本身不应该包含本头文件
#include "Hazel/Core/Application.h"
#include "Hazel/Core/KeyCodes.h"
#include "Hazel/Core/MouseCodes.h"
#include "Hazel/ImGui/ImGuiLayer.h"
#include "Hazel/Core/Input.h"
#include "Hazel/Core/Log.h"
#include "Hazel/Core/TimeStep.h"
#include "Hazel/Renderer/OrthographicCameraController.h"

#include "Hazel/Core/Layer.h"

#include "Hazel/Scene/Scene.h"
#include "Hazel/Scene/Entity.h"
#include "Hazel/Scene/Components.h"
//------renderer---------------
#include "Hazel/Renderer/Renderer.h"
#include "Hazel/Renderer/Renderer2D.h"
#include "Hazel/Renderer/RenderCommand.h "

#include "Hazel/Renderer/Buffer.h"
#include "Hazel/Renderer/VertexArray.h"
#include "Hazel/Renderer/Shader.h"
#include "Hazel/Renderer/Texture.h"
#include "Hazel/Renderer/FrameBuffer.h"
#include "Hazel/Renderer/OrthographicCamera.h"
//------渲染效果---------------
#include "Hazel/Renderer/ParticleSystem.h"
//------辅助工具---------------
#include "Hazel/Debug/Instrumentor.h"
#include "Hazel/Math/Math.h";
//------程序入口点--------------

//#include"Hazel/Core/EntryPoint.h"
//------------------------------
