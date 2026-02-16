#pragma once
#include "Window.h"
#include "imgui.h"
#include "EngineTypes.h"

class EngineWindow :
    public Window
{
public:
    using Window::Window;
    void Init();
    void Update(ObjectVec objectsToRender);

private:
    ImVec2 m_buttonSize;
    ImVec2 m_imGuiWindowSize;
    void SetImGuiElements();
};

