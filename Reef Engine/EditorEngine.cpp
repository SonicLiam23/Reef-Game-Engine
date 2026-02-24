#include "EditorEngine.h"
#include "EditorWindow.h"
#include "Object.h"
#include <iostream>
#include <fstream>

EditorEngine::EditorEngine() : m_isInitialized(false), m_isRunning(false)
{

}

EditorEngine::~EditorEngine()
{
	delete m_window;
}

void EditorEngine::Start(int windowScale, std::string windowName)
{

	m_window = new EditorWindow(windowScale, windowName);
	m_window->Start(this);

	m_isRunning = true;

	LoadObjects();

	for (const ObjectUPtr& obj : m_objects)
	{
		obj.get()->Start();
	}
}

void EditorEngine::Update()
{
	m_window->Update(m_objects);
	// do not run update on the objects themselves, this is the editor
	// detect which object to select

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		std::optional<Math::Vector2> mousePosOnViewport = m_window->GetViewport()->GetMousePos();
		
		if (mousePosOnViewport)
		{
			m_window->selectedObject = nullptr;
			for (ObjectUPtr& obj : m_objects)
			{
				if (obj->IsColliding(mousePosOnViewport.value()))
				{
					m_window->selectedObject = obj.get();
					break;
				}
			}
		}
	}
}


void EditorEngine::End()
{
	m_isRunning = false;
	SaveObjects();
}


///////////////////API///////////////////////


Object* EditorEngine::AddObject(const std::string objName)
{
	m_objects.emplace_back(std::make_unique<Object>());
	m_objects.back().get()->name = objName;
	return m_objects.back().get();
}

bool EditorEngine::IsRunning()
{
	return m_isRunning;
}

void EditorEngine::SaveObjects()
{
	nlohmann::json j = nlohmann::json::array();
	for (const ObjectUPtr& obj : m_objects)
	{
		j.push_back(*obj);
	}
	std::ofstream file("SavedObjects.json");
	if (!file) throw std::runtime_error("Failed to open file for writing");
	file << j.dump(4);
	file.close();
}

void EditorEngine::LoadObjects()
{
	m_objects.clear();
	std::ifstream file;
	file.open("SavedObjects.json");
	if (!file)
	{
		return;
	}
	nlohmann::json j;
	file >> j;
	for (auto objJson : j)
	{
		auto objFromJson = objJson.get<Object>();
		ObjectUPtr obj = std::make_unique<Object>(std::move(objFromJson));
		if (obj)
		{
			m_objects.push_back(std::move(obj));
		}

	}

	file.close();
}

