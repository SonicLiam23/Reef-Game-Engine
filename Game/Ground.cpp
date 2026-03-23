#include "Ground.h"
#include "Object.h"
#include "Engine.h"

void Ground::Start()
{
	AttachedObject->AddPhysics(Object::PhysicsType::STATIC);
}

void Ground::Update()
{

}
