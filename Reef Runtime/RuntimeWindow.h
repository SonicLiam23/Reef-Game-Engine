#pragma once
#include "Window.h"
class RuntimeEngine;
class RuntimeWindow :
    public Window
{
public:
    using Window::Window;
    void Start(RuntimeEngine* engine);
    // Inherited via Window
    void Update(ObjectVec& objects) override;

	Math::Vector2i ConvertScreenPointToWorldCoords(Math::Vector2i point) override;

private:
    RuntimeEngine* m_attachedEngine;

};

