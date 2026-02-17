#pragma once
#include "Window.h"
#include "imgui.h"
#include "EngineTypes.h"

// contains the Editor OS window and the ImGui windows inside it.
class EditorWindow :
    public Window
{
public:
    using Window::Window;
    void Init();
    void Update(ObjectVec& objectsToRender);

private:
    ImVec2 m_buttonSize;
    ImVec2 m_imGuiWindowSize;
    ImGuiWindowFlags m_dockspaceflags{};
    ImGuiWindowFlags m_viewportFlags{};
    sf::RenderTexture* m_viewPortTex;
    
    void SetImGuiElements();
};

 