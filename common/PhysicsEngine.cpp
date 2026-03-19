#include "PhysicsEngine.h"
#include "PhysicsComponent.h"
PhysicsEngine::PhysicsEngine(Math::Vector2f gravity) : m_world(gravity)
{
	PhysicsComponent::PhysEngine = this;
}

void PhysicsEngine::Start()
{
}

void PhysicsEngine::Update()
{
	m_world.Step(1.0f / 60.0f, 8, 3);
}

void PhysicsEngine::End()
{

}

void PhysicsEngine::SetGravity(Math::Vector2f gravity)
{
	m_world.SetGravity(gravity);
}
