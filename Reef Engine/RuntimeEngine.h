#pragma once
#include "EngineState.h"
class RuntimeEngine :
    public EngineState
{
    // Inherited via EngineState
    void Start() override;
    void Update() override;
    void End() override;
};

