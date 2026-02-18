#pragma once
#include <string>
#include "EngineTypes.h"
class EditorWindow;
class EditorEngine
{
public:
    EditorEngine();
    void Start(int windowScale = 100, std::string windowName = "Reef Engine");
    void Update();
    void End();

    void AddObject(Object* objToAdd);
    bool IsRunning();

private:
    EditorWindow* m_window;
    ObjectVec m_objects;

    bool m_isInitialized;
    bool m_isRunning;

};

