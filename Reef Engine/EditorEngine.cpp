#include "EditorEngine.h"
#include "EditorWindow.h"
#include "Object.h"
#include <iostream>
#include <fstream>
#include <random>

EditorEngine::EditorEngine() : m_isInitialized(false), m_isRunning(false)
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
		std::optional<Math::Vector2f> mousePosOnViewport = m_window->GetViewport()->GetMousePos();
		
		if (mousePosOnViewport)
		{
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
}


void EditorEngine::End()
{
	m_isRunning = false;
	SaveObjects();
}


///////////////////API///////////////////////


Object* EditorEngine::AddObject(const std::string objName)
{
	Object* obj = m_objects.emplace_back(std::make_unique<Object>()).get();

	obj->name = objName;
	obj->SetID(std::to_string(rand()));
	objectIDMap[obj->GetID()] = m_objects.size();

	obj->Start();
	return obj;
}

void EditorEngine::DestroyObject(const std::string& id)
{
	// O(1) deletion using IDs
	if (objectIDMap.count(id) == 0)
	{
		assert(false);
		return;
	}
	size_t ind = objectIDMap[id];
	if (ind != m_objects.size() - 1)
	{
		// swapping with the back, so update the map
		std::swap(m_objects[ind], m_objects.back());

		// ind now holds the old back
		Object* movedObj = m_objects[ind].get();
		objectIDMap[movedObj->GetID()] = ind;
	}

	// now remove the object to deletes ID from the map
	objectIDMap.erase(id);
	m_objects.pop_back();
}

void EditorEngine::DestroyObject(Object* toDelete)
{
	DestroyObject(toDelete->GetID());
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

