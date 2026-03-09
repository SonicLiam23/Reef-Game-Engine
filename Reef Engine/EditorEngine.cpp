#include "EditorEngine.h"
#include "EngineTypes.h"
#include "EditorWindow.h"
#include "SpriteUtils.h"
#include "Object.h"
#include <iostream>
#include <fstream>
#include <random>
#include <windows.h>
#include <string>
#include "Input.h"

EditorEngine::EditorEngine() : Engine()
{
	srand(time(NULL));
}

EditorEngine::~EditorEngine()
{
	delete m_window;
}

EditorEngine& EditorEngine::Get()
{
	static EditorEngine instance;
	return instance;
}

void EditorEngine::Start()
{
	LoadLibraryA("Game.dll");

	SpriteUtils::Init();

	m_window = new EditorWindow(100, "Reef Engine");
	m_window->Start(this);

	m_isRunning = true;

	LoadObjects();

	for (const ObjectUPtr& obj : m_objects)
	{
		obj.get()->Init();
	}
}

void EditorEngine::Update()
{
	m_window->Update(m_objects);
	// do not run update on the objects themselves, this is the editor
	// detect which object to select

	if (Input::GetMouseButton(Input::MouseButton::Left).clicked == Input::SingleClick)
	{
		// get mouse position relative to the viewport
		std::optional<Math::Vector2f> mousePosOnViewport = m_window->GetViewport()->GetMousePos();
		
		if (mousePosOnViewport)
		{
			m_window->SetSelectedObject(nullptr);
			for (ObjectUPtr& obj : m_objects)
			{
				if (obj->IsColliding(mousePosOnViewport.value()))
				{
					m_window->SetSelectedObject(obj.get());
					break;
				}
			}
		}
	}

	for (int i = 0; i < m_objects.size(); ++i)
	{
		ObjectUPtr& obj = m_objects[i];
		if (obj->MarkedForDeletion())
		{
			DestroyObject(obj->GetID());
			m_window->SetSelectedObject(nullptr);
			--i;
		}
	}
}


void EditorEngine::End()
{
	SaveObjects();
	for (ObjectUPtr& obj : m_objects)
	{
		DestroyObject(obj->GetID());
	}
	m_isRunning = false;
	
	SpriteUtils::End();

}