#include "Engine.h"

Engine::Engine() 
	: m_initialized(false), m_running(false)
{

}

void Engine::Init(Math::Vector2u windowSize)
{

}

void Engine::Start(EngineStates startingState)
{
	m_engineStates[EDITOR] = new EditorEngine;
	m_engineStates[RUNTIME] = new RuntimeEngine;

	m_currentState = m_engineStates[startingState];
	m_currentState->Start();
}

void Engine::Update()
{
	m_currentState->Update();
}


