#pragma once
#include "EngineAPI.h"
#include "box2d/box2d.h"
#include "Vector2.h"
class Object;
class ENGINE_API PhysicsEngine
{
private:
	b2World m_world;

public:
	PhysicsEngine(Math::Vector2f gravity = {0.0f, 100.0f});
	void Start();
	void Update();
	void End();
	void SetGravity(Math::Vector2f gravity);

private:
	friend class PhysicsComponent;
};

