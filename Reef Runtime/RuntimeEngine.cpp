#include "RuntimeEngine.h"
#include "RuntimeWindow.h"
#include "Object.h"
#include <windows.h>

RuntimeEngine& RuntimeEngine::Get()
{
	static RuntimeEngine instance;
	return instance;
}

void RuntimeEngine::Start()
{
	LoadLibraryA("Game.dll");

	m_isRunning = true;

	m_window = new RuntimeWindow(100, "Reef Engine");
	m_window->Start(this);

	LoadObjects();

	for (ObjectUPtr& obj : m_objects)
	{
		obj->Init();
		obj->Start();
	}
}

void RuntimeEngine::Update()
{
	for (ObjectUPtr& obj : m_objects)
	{
		obj->Update();
	}
	m_window->Update(m_objects);
	for (int i = 0; i < m_objects.size(); ++i)
	{
		ObjectUPtr& obj = m_objects[i];
		if (obj->MarkedForDeletion())
		{
			DestroyObject(obj->GetID());
			--i;
		}
	}
}

void RuntimeEngine::End()
{
	for (ObjectUPtr& obj : m_objects)
	{
		obj->Destroy();
	}
	m_isRunning = false;
}