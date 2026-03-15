#pragma once
class Window; class Camera;
#include <string>
#include "EngineTypes.h"
#include "Object.h"
#include "EngineAPI.h"
class ENGINE_API Engine
{
public:
	Engine();
	~Engine();

	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void End() = 0;

	Object* AddObject(const std::string objName = "NO_NAME");
	void DestroyObject(const std::string& id);
	void DestroyObject(Object* toDelete);

	bool IsRunning();

	void SaveObjects();
	void LoadObjects();

	virtual void SetCameraPos(const Math::Vector2f& newPosition) = 0;
	virtual void SetCameraPos(Object* obj) = 0;
	virtual void AttachCameraToObject(Object* obj) = 0;

	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;

	Engine(Engine&&) = default;
	Engine& operator=(Engine&&) = default;

protected:
	ObjectVec m_objects;

	bool m_isInitialized;
	bool m_isRunning;
	

};

