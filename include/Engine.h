#pragma once
class Object; class EngineImpl;
#include "EngineAPI.h"
#include <string>
#include "Vector2.h"

// The engine API that the user interacts with, this is a wrapper around the EngineImpl (and its member m_windowBase), which contains the actual implementation of the engine. 
// This is done to hide implementation details from the user and to allow for different implementations of the engine (e.g. editor vs runtime).

class ENGINE_API Engine
{
public:
	static Engine& Get();

	Object* AddObject(const std::string objName = "NO_NAME");
	void DestroyObject(const std::string& id);
	void DestroyObject(Object* toDelete);

	bool IsRunning();

	void SetCameraPos(const Math::Vector2f& newPosition);
	void SetCameraPos(Object* obj);
	void AttachCameraToObject(Object* obj);
		
private:
	friend class EngineImpl;
	EngineImpl* m_impl;
};

