#pragma once
#include "box2d/b2_body.h"
#include "box2d/b2_polygon_shape.h"
#include "box2d/b2_fixture.h"
#include "Object.h"
class PhysicsEngine;
class PhysicsComponent
{
private:
	b2BodyDef m_bodyDef;
	b2Body* m_body;
	b2PolygonShape m_shape;
	b2FixtureDef m_fixDef;
	Object* m_attachedObj;

public:
	PhysicsComponent(Object* object, Object::PhysicsType type = Object::PhysicsType::STATIC);
	void Update();

	static PhysicsEngine* PhysEngine;
};

