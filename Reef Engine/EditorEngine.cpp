#include "EditorEngine.h"
#include "EditorWindow.h"
#include "Object.h"
#include <iostream>
#include <fstream>
#include <random>

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

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
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
	m_isRunning = false;
	SaveObjects();
}


///////////////////API///////////////////////




