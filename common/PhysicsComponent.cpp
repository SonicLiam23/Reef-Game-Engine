#include "PhysicsComponent.h"
#include "PhysicsEngine.h"
#include "box2d/b2_draw.h"
#include <iostream>
PhysicsEngine* PhysicsComponent::PhysEngine = nullptr;
void PhysicsComponent::InitPhysicsObject()
{

}
PhysicsComponent::PhysicsComponent(Object* object, Object::PhysicsType type) : m_attachedObj(object), m_type(type)
{
	// testing to get it working, will integrate properly later
	float conversion = PhysEngine->pixelsPerMetre;
	b2Vec2 b2position = (b2Vec2)m_attachedObj->GetPosition();
	b2position.x /= conversion;
	b2position.y /= conversion;

	switch (m_type)
	{
	case Object::PhysicsType::DYNAMIC:
		m_bodyDef.type = b2_dynamicBody;	
		m_bodyDef.position.Set(b2position.x, b2position.y);
		m_body = PhysEngine->m_world.CreateBody(&m_bodyDef);
		SetSize(m_attachedObj->GetSize());
		m_fixDef.shape = &m_shape;
		m_fixDef.density = 1.0f;
		m_fixDef.friction = 0.3f;
		m_body->CreateFixture(&m_fixDef);

		break;
	case Object::PhysicsType::STATIC:
		m_bodyDef.type = b2_staticBody;
		m_bodyDef.position.Set(b2position.x, b2position.y);
		m_body = PhysEngine->m_world.CreateBody(&m_bodyDef);
		SetSize(m_attachedObj->GetSize());
		m_body->CreateFixture(&m_shape, 0.0f);

		break;
	case Object::PhysicsType::KINEMATIC:
		break;
	default:
		break;
	}
	m_body->SetAwake(true);
}

void PhysicsComponent::Update()
{
	// convert box2d metres to pixels
	auto pos = m_body->GetPosition();
	pos.x *= PhysEngine->pixelsPerMetre;
	pos.y *= PhysEngine->pixelsPerMetre;
	// -y is up in sfml
	//pos.y = -pos.y;

	
	m_attachedObj->SetPosition({ pos.x, pos.y});
	m_attachedObj->SetRotation(m_body->GetAngle());
	

	if (m_type == Object::PhysicsType::DYNAMIC)
	{
		std::cout << "DYNAMIC: " << pos.x << ", " << pos.y << std::endl;
	}
	else
	{
		std::cout << "STATIC: " << pos.x << ", " << pos.y << std::endl;
	}
}

void PhysicsComponent::SetPosition(Math::Vector2f pixelCoords)
{
	b2Vec2 pos;
	pos.x = pixelCoords.x / PhysEngine->pixelsPerMetre;
	pos.y = pixelCoords.y / PhysEngine->pixelsPerMetre;
	m_body->SetTransform(pos, m_body->GetAngle());
}

void PhysicsComponent::SetRotation(float angle)
{
	m_body->SetTransform(m_body->GetPosition(), angle);
}

void PhysicsComponent::SetSize(Math::Vector2f newSize)
{
	newSize.x /= PhysEngine->pixelsPerMetre;
	newSize.y /= PhysEngine->pixelsPerMetre;
	m_shape.SetAsBox(newSize.x / 2, newSize.y / 2);
}

void PhysicsComponent::AddForce(float strength, Math::Vector2f direction)
{
	direction.Normalize();
	direction.x *= strength;
	direction.y *= strength;

	// I dont think the naming is right but this is all internal so only I will see it.
	AddForce(direction);
}

void PhysicsComponent::AddForce(Math::Vector2f force)
{
	m_body->ApplyForceToCenter(force, false);
}

void PhysicsComponent::SetVelocity(Math::Vector2f newVelocity)
{
	m_body->SetLinearVelocity(newVelocity);
}

void PhysicsComponent::AddImpulse(float strength, Math::Vector2f direction)
{
	direction.Normalize();
	direction.x *= strength;
	direction.y *= strength;

	// I dont think the naming is right but this is all internal so only I will see it.
	AddImpulse(direction);
}

void PhysicsComponent::AddImpulse(Math::Vector2f force)
{
	m_body->ApplyLinearImpulseToCenter(force, false);
}

void PhysicsComponent::SetGravityScale(float scale)
{
	m_body->SetGravityScale(scale);
}
