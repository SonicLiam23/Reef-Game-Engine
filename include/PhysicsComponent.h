#pragma once
#include "EngineAPI.h"
#include "box2d/b2_body.h"
#include "box2d/b2_polygon_shape.h"
#include "box2d/b2_fixture.h"
#include "Object.h"
#include "Vector2.h"

// helper macro
#define PIXELS_TO_METRES(p) (PhysEngine->GetPixelsPerMetre() / p)
#define METRES_TO_PIXELS(p) (PhysEngine->GetPixelsPerMetre() * p)

class PhysicsEngine;
class ENGINE_API PhysicsComponent
{
private:
	b2BodyDef m_bodyDef;
	b2Body* m_body;
	b2PolygonShape m_shape;
	b2FixtureDef m_fixDef;
	Object* m_attachedObj;
	Object::PhysicsType m_type;
	void InitPhysicsObject();
	void Update();
	// called when Object::SetPosition() is, update the physics object along with it
	void SetPosition(Math::Vector2f pixelCoords);
	void SetRotation(float angle);

	// for Update(). Might be overkill but only object contains this anyway.
	friend class Object;

public:
	PhysicsComponent(Object* object, Object::PhysicsType type = Object::PhysicsType::STATIC);
	void SetSize(Math::Vector2f newSize);

	static PhysicsEngine* PhysEngine;

	// applies force to centre
	void AddForce(float strength, Math::Vector2f direction);
	// applies force to centre
	void AddForce(Math::Vector2f force);

	void SetVelocity(Math::Vector2f newVelocity);

	void AddImpulse(float strength, Math::Vector2f direction);
	void AddImpulse(Math::Vector2f force);

	void SetGravityScale(float scale);
};

