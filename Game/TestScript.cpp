#include "TestScript.h"
#include <iostream>
#include "Input.h"
#include "Engine.h"

void TestScript::Update()
{
		
}

void TestScript::Start()
{
	name = "test passed";
	Engine::Get().AttachCameraToObject(AttachedObject);
}
