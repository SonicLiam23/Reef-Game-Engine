#pragma once
#include "Vector2.h"
#include "EngineState.h"
#include "EditorEngine.h"
#include "RuntimeEngine.h"

enum EngineStates
{
	RUNTIME,
	EDITOR
};

class Window;

class Engine
{
public:
	Engine();
	void Init(Math::Vector2u windowSize);
	void Start(EngineStates startingState = RUNTIME);
	
	void Update();

private:
	bool m_running;
	bool m_initialized;

	EngineState* m_currentState = nullptr;
	EngineState* m_engineStates[2] = {};

};

