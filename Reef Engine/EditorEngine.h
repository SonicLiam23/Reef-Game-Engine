#pragma once
#include "EngineState.h"
class EditorEngine :
    public EngineState
{
    // Inherited via EngineState
    void Start() override;
    void Update() override;
    void End() override;
};

