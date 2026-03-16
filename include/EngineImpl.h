#pragma once
class Window; class Engine;
#include <string>
#include "EngineTypes.h"
#include "Object.h"
#include "EngineAPI.h"


class ENGINE_API EngineImpl
{
public:
	EngineImpl();
	~EngineImpl();

	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void End() = 0;

	Object* AddObject(const std::string objName = "NO_NAME");
	void DestroyObject(const std::string& id);
	void DestroyObject(Object* toDelete);

	bool IsRunning();

	void SaveObjects();
	void LoadObjects();

	EngineImpl(const EngineImpl&) = delete;
	EngineImpl& operator=(const EngineImpl&) = delete;

	EngineImpl(EngineImpl&&) = default;
	EngineImpl& operator=(EngineImpl&&) = default;

protected:
	ObjectVec m_objects;

	bool m_isInitialized;
	bool m_isRunning;
	Engine* m_engineAPI;
	Window* m_windowBase;

private:
	friend class Engine;
};

