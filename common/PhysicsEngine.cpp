#include "PhysicsEngine.h"
PhysicsEngine::PhysicsEngine(Math::Vector2f gravity) : m_world(gravity)
{
	
}

void PhysicsEngine::Start()
{
}

void PhysicsEngine::Update()
{
}

void PhysicsEngine::End()
{
}

void PhysicsEngine::UpdateObject(Object* object)
{
}

void PhysicsEngine::SetGravity(Math::Vector2f gravity)
{
	m_world.SetGravity(gravity);
}
