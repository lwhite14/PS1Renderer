#include "debug_window.h"

#include <GLFW/glfw3.h>

void DebugWindow::DrawElements()
{
    //ImGui::ShowDemoWindow();

    ImGuiWindowFlags windowFlags = 0;
    windowFlags |= ImGuiWindowFlags_NoTitleBar;
    windowFlags |= ImGuiWindowFlags_NoBackground;
    windowFlags |= ImGuiWindowFlags_NoResize;

    ImGui::Begin("Debug", NULL, windowFlags);
    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
    ImGui::Text("Light Editor");
    ImGui::DragFloat3("Position [Point]", lightPos, 0.25f, -200.0f, 200.0f);
    ImGui::DragFloat3("Diffuse", lightDiffuse, 0.01f, 0.0f, 1.0f);
    ImGui::DragFloat3("Ambient", lightAmbient, 0.01f, 0.0f, 1.0f);
    ImGui::Text("Object Editor");
    ImGui::Text("Used To Move Selected Object(s) [If Selected]");
    ImGui::DragFloat3("Position [Object]", objectPos, 0.25f, -200.0f, 200.0f);
    ImGui::DragFloat("Rotation [Object]", objectRot, 0.25f, -200.0f, 200.0f);
    ImGui::Text("Press 'Left Shift' to toggle to this debug menu");
    ImGui::SetWindowPos(ImVec2(0, 0));
    ImGui::SetWindowSize(ImVec2(500, 260));
    ImGui::End();
}

DebugWindow::DebugWindow()
{

}

void DebugWindow::Init(GLFWwindow* window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460");
}

void DebugWindow::PerFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    DrawElements();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

void DebugWindow::CleanUp()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}