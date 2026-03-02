#pragma once
#include "EngineAPI.h"
#include "Engine.h"
class RuntimeWindow;
class RuntimeEngine :
    public Engine
{
public:
    static RuntimeEngine& Get();

    void Start() override;
    void Update() override;
    void End() override;

private:
    RuntimeEngine() = default;
    ~RuntimeEngine() = default;

    RuntimeWindow* m_window;
};

