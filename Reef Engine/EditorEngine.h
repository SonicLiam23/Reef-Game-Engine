#pragma once
#include <string>
#include "EngineTypes.h"
#include <unordered_map>
#include "Engine.h"

class EditorWindow;
class EditorEngine : public Engine
{
public:
    // singleton
    static EditorEngine& Get();

    void Start() override;
    void Update() override;
    void End() override;

private:
    EditorEngine();
    ~EditorEngine();

    EditorWindow* m_window;
};

