#pragma once
#include <string>
#include "EngineTypes.h"
#include <unordered_map>

class EditorWindow;
class EditorEngine
{
public:
    EditorEngine();
    ~EditorEngine();
    void Start(int windowScale = 100, std::string windowName = "Reef Engine");
    void Update();
    void End();

    Object* AddObject(const std::string objName = "NO_NAME");
    bool IsRunning();

    void SaveObjects();
    void LoadObjects();

private:
    EditorWindow* m_window;
    ObjectVec m_objects;

    bool m_isInitialized;
    bool m_isRunning;

};

