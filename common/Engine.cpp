#include "Engine.h"
#include "Object.h"
#include "EngineImpl.h"
#include "Window.h"

Engine& Engine::Get()
{
	static Engine instance;
	return instance;
}

Object* Engine::AddObject(const std::string objName)
{
	return m_impl->AddObject(objName);
}

void Engine::DestroyObject(const std::string& id)
{
	// O(1) deletion using IDs
	m_impl->DestroyObject(id);
}

void Engine::DestroyObject(Object* toDelete)
{
	m_impl->DestroyObject(toDelete->GetID());
}

bool Engine::IsRunning()
{
	return m_impl->IsRunning();
}

void Engine::SetCameraPos(const Math::Vector2f& newPosition)
{
	m_impl->m_windowBase->SetCameraPosition(newPosition);
}

void Engine::SetCameraPos(Object* obj)
{
	m_impl->m_windowBase->SetCameraPosition(obj);
}

void Engine::AttachCameraToObject(Object* obj)
{
	m_impl->m_windowBase->AttachCameraToObject(obj);
}
