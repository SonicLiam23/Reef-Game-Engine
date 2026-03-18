#pragma once
#include "box2d/box2d.h"
#include "Vector2.h"
class Object;
class PhysicsEngine
{
private:
	b2World m_world;

public:
	PhysicsEngine(Math::Vector2f gravity = {0.0f, -9.8f});
	void Start();
	void Update();
	void End();
	void UpdateObject(Object* object);
	void SetGravity(Math::Vector2f gravity);
};

