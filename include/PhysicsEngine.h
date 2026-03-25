#pragma once
#include "EngineAPI.h"
#include "box2d/box2d.h"
#include "Vector2.h"
class Object;
class ENGINE_API PhysicsEngine
{

public:
	PhysicsEngine(Math::Vector2f gravity = {0.0f, 10.0f}, float PPM = 30.f);
	
	void Start();
	void Update();
	void End();
	void SetGravity(Math::Vector2f gravity);
	float pixelsPerMetre;

private:
	friend class PhysicsComponent;
	
	b2World m_world;
};

