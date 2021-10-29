#include"hzpch.h"

#include"imgui.h"
#include"ImGuiLayer.h"
#include"Platform/OpenGL/ImGuiOpenGLRender.h"

#include "Hazel/Application.h"
//临时使用
#include<GLFW/glfw3.h>
#include <glad/glad.h>
Hazel::ImGuiLayer::ImGuiLayer()
	:Layer("ImGuiLayer")
{
}


Hazel::ImGuiLayer::~ImGuiLayer()
{
}

void Hazel::ImGuiLayer::OnUpdate()
{
    ImGuiIO& io = ImGui::GetIO();
	Application& app = Application::Get();
    io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

    float time = (float)glfwGetTime();
    io.DeltaTime = m_time>0.0f ?time- m_time:(1.0f/60.0f);
    m_time = time;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    
    static bool show = true;
    ImGui::ShowDemoWindow(&show);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    
}

void Hazel::ImGuiLayer::OnEvent(Event& event)
{
    EventDispatcher d(event);
    d.Dispatch<MouseButtonPressedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
    d.Dispatch<MouseButtonReleasedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
    d.Dispatch<MouseMoveEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnMouseMoveEvent));

    d.Dispatch<MouseScrolledEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));

    d.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
    d.Dispatch<KeyPressEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
    d.Dispatch<KeyReleasedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
    d.Dispatch<KeyTypedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));

}

void Hazel::ImGuiLayer::OnAttach()
{
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGuiIO& io = ImGui::GetIO();
	io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
	io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
    //此处最终会使用Hazelkeycode
    //现在暂时使用glfw的keycode
    io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
    io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
    io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
    io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
    io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
    io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
    io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
    io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
    io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
    io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
    io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
    io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
    io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
    io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
    io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
    io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
    io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
    io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
    io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
    io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
    io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

    //初始化opengl3
    ImGui_ImplOpenGL3_Init("#version 410");


}

void Hazel::ImGuiLayer::OnDetach()
{

}

bool Hazel::ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
{
    /*
	ImVec2      MousePos;                       // Mouse position, in pixels. Set to ImVec2(-FLT_MAX, -FLT_MAX) if mouse is unavailable (on another screen, etc.)
	bool        MouseDown[5];                   // Mouse buttons: 0=left, 1=right, 2=middle + extras (ImGuiMouseButton_COUNT == 5). Dear ImGui mostly uses left and right buttons. Others buttons allows us to track if the mouse is being used by your application + available to user as a convenience via IsMouse** API.
	float       MouseWheel;                     // Mouse wheel Vertical: 1 unit scrolls about 5 lines text.
	float       MouseWheelH;                    // Mouse wheel Horizontal. Most users don't have a mouse with an horizontal wheel, may not be filled by all backends.
	ImGuiID     MouseHoveredViewport;           // (Optional) When using multiple viewports: viewport the OS mouse cursor is hovering _IGNORING_ viewports with the ImGuiViewportFlags_NoInputs flag, and _REGARDLESS_ of whether another viewport is focused. Set io.BackendFlags |= ImGuiBackendFlags_HasMouseHoveredViewport if you can provide this info. If you don't imgui will infer the value using the rectangles and last focused time of the viewports it knows about (ignoring other OS windows).
	bool        KeyCtrl;                        // Keyboard modifier pressed: Control
	bool        KeyShift;                       // Keyboard modifier pressed: Shift
	bool        KeyAlt;                         // Keyboard modifier pressed: Alt
	bool        KeySuper;                       // Keyboard modifier pressed: Cmd/Super/Windows
	bool        KeysDown[512];                  // Keyboard keys that are pressed (ideally left in the "native" order your engine has access to keyboard keys, so you can use your own defines/enums for keys).
	float       NavInputs[ImGuiNavInput_COUNT];
    */
    ImGuiIO& io = ImGui::GetIO();
    io.MouseDown[e.GetMouseButton()] = true;
    return false;
}

bool Hazel::ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MouseDown[e.GetMouseButton()] = false;
    return false;
}

bool Hazel::ImGuiLayer::OnMouseMoveEvent(MouseMoveEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();
    io.MousePos = ImVec2(e.GetX(), e.GetY());
    return false;
}

bool Hazel::ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
{
    ImGuiIO& io = ImGui::GetIO();
    //Horizontal
    io.MouseWheelH += e.GetXOffset();
    // Vertical
    io.MouseWheel += e.GetYOffset();


    return false;
}

bool Hazel::ImGuiLayer::OnKeyPressedEvent(KeyPressEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();
    io.KeysDown[e.GetKeyCode()] = true;
	io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
	io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
	io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
	io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
    return false;
}

bool Hazel::ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.KeysDown[e.GetKeyCode()] = false;
    
    return false;
}

bool Hazel::ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
{
    ImGuiIO& io = ImGui::GetIO();
    unsigned int c = e.GetKeyCode();
    if (c>0&&c<0x10000)
        io.AddInputCharacter((unsigned short)c);
    return false;
}



bool Hazel::ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
{
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(e.GetWindth(), e.GetHight());
    io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
    glViewport(0, 0, e.GetWindth(), e.GetHight());

    return false;
}
