#pragma once
#include <unordered_map>
#include "EngineImpl.h"

class EditorWindow;
class EditorEngine : public EngineImpl
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

