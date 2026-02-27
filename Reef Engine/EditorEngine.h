#pragma once
#include <string>
#include "EngineTypes.h"
#include <unordered_map>

class EditorWindow;
class EditorEngine
{
public:
    // singleton
    static EditorEngine& Get();


    void Start(int windowScale = 100, std::string windowName = "Reef Engine");
    void Update();
    void End();

    Object* AddObject(const std::string objName = "NO_NAME");
    void DestroyObject(const std::string& id);
    void DestroyObject(Object* toDelete);

    bool IsRunning();

    void SaveObjects();
    void LoadObjects();

private:
    EditorEngine();
    ~EditorEngine();

    EditorWindow* m_window;
    ObjectVec m_objects;

    bool m_isInitialized;
    bool m_isRunning;

};

