#pragma once
#include "Window.h"
#include "imgui.h"
#include "EngineTypes.h"
#include <unordered_map>

// contains the Editor OS window and the ImGui windows inside it.
class EditorWindow :
    public Window
{
public:
    using Window::Window;
    void Init();
    void Update(ObjectVec& objectsToRender) override;


private:
    ImVec2 m_buttonSize;
    ImVec2 m_imGuiWindowSize;
    ImGuiWindowFlags m_dockspaceflags{};
    ImGuiWindowFlags m_viewportFlags{};
    sf::RenderTexture* m_viewPortTex;

    std::unordered_map<Object*, sf::RectangleShape> m_outlines;
    
    void SetImGuiElements();
};

 