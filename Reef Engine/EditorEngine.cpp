#include "EditorEngine.h"
#include "EditorWindow.h"
#include "Object.h"
#include <iostream>

EditorEngine::EditorEngine() : m_isInitialized(false), m_isRunning(false)
{
}

void EditorEngine::Start(int windowScale, std::string windowName)
{

	m_window = new EditorWindow(windowScale, windowName);
	m_window->Start(this);

	m_isRunning = true;
}

void EditorEngine::Update()
{
	m_window->Update(m_objects);
	// do not run update on the objects themselves, this is the editor
	// detect which object to select

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		

		auto mousePosOnViewport = m_window->GetViewport()->GetMousePos();
		
		if (mousePosOnViewport)
		{
			m_window->selectedObject = nullptr;
			for (Object* obj : m_objects)
			{
				if (obj->IsColliding(mousePosOnViewport.value()))
				{
					m_window->selectedObject = obj;
					break;
				}
			}
		}

	}
}


void EditorEngine::End()
{
	delete m_window;
}


///////////////////API///////////////////////


void EditorEngine::AddObject(Object* objToAdd)
{
	m_objects.push_back(objToAdd);
}

bool EditorEngine::IsRunning()
{
	return m_isRunning;
}
