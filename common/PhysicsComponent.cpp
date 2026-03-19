#include "PhysicsComponent.h"
#include "PhysicsEngine.h"
PhysicsEngine* PhysicsComponent::PhysEngine = nullptr;
PhysicsComponent::PhysicsComponent(Object* object, Object::PhysicsType type) : m_attachedObj(object)
{
	float density;
	switch (type)
	{
	case Object::PhysicsType::DYNAMIC:
		m_bodyDef.type = b2_dynamicBody;
		m_shape.SetAsBox((object->GetSize().x / 2.0f) / 30.0f, (object->GetSize().y / 2.0f) / 30.0f);
		m_fixDef.shape = &m_shape;
		m_fixDef.density = 1.0f;
		m_fixDef.friction = 0.3f;
		break;
	case Object::PhysicsType::STATIC:
		m_bodyDef.type = b2_staticBody;
		// TEMP WHILST I FIGURE OUT HOW IT WORKS, MUST CHANGE THIS!!!!!!!!!!!!!!!!!!!!!
		m_shape.SetAsBox((20 / 2.0f) / 30.0f, 2000 / 30.0f);
		m_bodyDef.position.Set(0, -10);
		// END TEMP
		m_fixDef.density = 0.0f;

		
		break;
	case Object::PhysicsType::KINEMATIC:
		break;
	default:
		break;
	}

	m_body = PhysEngine->m_world.CreateBody(&m_bodyDef);
	m_body->CreateFixture(&m_fixDef);
	

}

void PhysicsComponent::Update()
{
	// convert box2d metres to pixels
	auto pos = m_body->GetPosition();
	pos.x /= 30.0f;
	pos.y /= 30.0f;
	m_attachedObj->SetPosition({ pos.x, pos.y });
}