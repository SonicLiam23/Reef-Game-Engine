#include "Engine.h"
#include "Object.h"
#include "json.hpp"
#include <fstream>
#include "SerializableFactory.h"

Engine::Engine() : m_isInitialized(false), m_isRunning(false)
{
}

Object* Engine::AddObject(const std::string objName)
{
	Object* obj = m_objects.emplace_back(std::make_unique<Object>()).get();

	obj->name = objName;
	obj->SetID(std::to_string(rand()));
	Object::GetIDMap()[obj->GetID()] = m_objects.size() - 1;

	obj->Init();
	return obj;
}

void Engine::DestroyObject(const std::string& id)
{
	// O(1) deletion using IDs
	if (Object::GetIDMap().count(id) == 0)
	{
		assert(false);
		return;
	}
	size_t ind = Object::GetIDMap()[id];
	if (ind != m_objects.size() - 1)
	{
		// swapping with the back, so update the map
		std::swap(m_objects[ind], m_objects.back());

		// ind now holds the old back
		Object* movedObj = m_objects[ind].get();
		Object::GetIDMap()[movedObj->GetID()] = ind;
	}

	// now remove the object to deletes ID from the map
	Object::GetIDMap().erase(id);
	m_objects.pop_back();
}

void Engine::DestroyObject(Object* toDelete)
{
	DestroyObject(toDelete->GetID());
}

bool Engine::IsRunning()
{
	return m_isRunning;
}

void Engine::SaveObjects()
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

void Engine::LoadObjects()
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
		auto obj = std::make_unique<Object>(objJson);
		if (obj)
		{
			// do this before because when we std::move the ptr wont be in the same place, so I dont need to subtract one.
			Object::GetIDMap()[obj->GetID()] = m_objects.size();
			m_objects.push_back(std::move(obj));
		}
	}
	file.close();
}