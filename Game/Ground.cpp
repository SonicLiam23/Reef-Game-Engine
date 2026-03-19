#include "Ground.h"
#include "Object.h"

void Ground::Start()
{
	AttachedObject->AddPhysics(Object::PhysicsType::STATIC);
}

void Ground::Update()
{

}
