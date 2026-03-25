#include "TestScript.h"
#include "Object.h"
#include "PhysicsComponent.h"

void TestScript::Update()
{
		
}

void TestScript::Start()
{
	AttachedObject->AddPhysics(Object::PhysicsType::DYNAMIC);
	//AttachedObject->physicsComponent->SetVelocity({ -10, 0 });
	AttachedObject->physicsComponent->AddImpulse({ 0, -30 });
}
