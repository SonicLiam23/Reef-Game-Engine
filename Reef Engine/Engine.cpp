#include "Engine.h"

Engine::Engine() 
	: m_initialized(false), m_running(false)
{
}

void Engine::Start()
{
	if (!m_initialized)
	{
		return;
	}
	m_running = true;
}

void Engine::Init(Math::Vector2u windowSize)
{
}

void Engine::Update()
{
}
