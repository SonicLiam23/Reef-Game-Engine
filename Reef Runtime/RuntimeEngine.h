#pragma once
#include "EngineAPI.h"
#include "EngineImpl.h"
#include <Windows.h>
class RuntimeWindow;
class RuntimeEngine :
    public EngineImpl
{
public:
    static RuntimeEngine& Get();

    void Start() override;
    void Update() override;
    void End() override;

private:
    RuntimeEngine() = default;
    ~RuntimeEngine();

    RuntimeWindow* m_window;
};

