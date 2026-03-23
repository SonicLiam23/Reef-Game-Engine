#include "PhysicsComponent.h"
#include "PhysicsEngine.h"
PhysicsEngine* PhysicsComponent::PhysEngine = nullptr;
void PhysicsComponent::InitPhysicsObject()
{

}
PhysicsComponent::PhysicsComponent(Object* object, Object::PhysicsType type) : m_attachedObj(object), m_type(type)
{
	// testing to get it working, will integrate properly later

	b2Vec2 b2position = (b2Vec2)m_attachedObj->GetPosition();

	switch (m_type)
	{
	case Object::PhysicsType::DYNAMIC:
		m_bodyDef.type = b2_dynamicBody;	
		m_bodyDef.position.Set(b2position.x, b2position.y);
		m_bodyDef.allowSleep = false;
		m_body = PhysEngine->m_world.CreateBody(&m_bodyDef);
		SetSize(m_attachedObj->GetSize());
		m_fixDef.shape = &m_shape;
		m_fixDef.density = 1.0f;
		m_fixDef.friction = 0.3f;
		m_body->CreateFixture(&m_fixDef);
		m_body->SetGravityScale(1.0f);

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
	pos.x /= 30.0f;
	pos.y /= 30.0f;
	// -y is up in sfml
	//pos.y = -pos.y;
	m_attachedObj->SetPosition({ pos.x, pos.y});

}

void PhysicsComponent::SetSize(Math::Vector2f newSize)
{
	// box2d uses metres, so convert pixels to metres ( *30 ) then divide by 2 
	newSize.x /= 60.0f;
	newSize.y /= 60.0f;	
	m_shape.SetAsBox(newSize.x, newSize.y);
}
