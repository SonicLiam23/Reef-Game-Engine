#include "TestScript.h"
#include <iostream>
#include "Input.h"
#include "Engine.h"
#include "Object.h"

void TestScript::Update()
{
		
}

void TestScript::Start()
{
	AttachedObject->AddPhysics(Object::PhysicsType::DYNAMIC);
}
