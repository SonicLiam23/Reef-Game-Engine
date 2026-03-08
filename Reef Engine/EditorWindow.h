#pragma once
#include "Window.h"
#include "imgui.h"
#include "EngineTypes.h"
#include <unordered_map>
#include "imgui_stdlib.h"



class EditorEngine; class Object;
// contains the Editor OS window and the ImGui windows inside it.
class EditorWindow :
    public Window
{
private:
    struct Viewport
    {
        EditorWindow* parent;
        ImVec2 position;
        ImVec2 size;
        bool mouseHovered;

        std::optional<Math::Vector2f> GetMousePos();
    };

    ImVec2 m_buttonSize;
    ImGuiWindowFlags m_dockspaceflags{};
    ImGuiWindowFlags m_viewportFlags{};
    sf::RenderTexture* m_viewPortTex;
    EditorEngine* m_attachedEngine;
    Viewport m_viewport;
    bool m_selectedObjectThisFrame;
    Object* m_selectedObject;
    int m_selectedScriptIdx;

    std::unordered_map<Object*, sf::RectangleShape> m_outlines;

    // values for input fields
    std::string m_inputID;


    void SetImGuiElements();
    
    friend struct Viewport;

public:
    using Window::Window;
    void Start(EditorEngine* engine);
    void Update(ObjectVec& objectsToRender) override;

    void SetSelectedObject(Object* newSelected);
    
    Viewport* GetViewport();

};





 