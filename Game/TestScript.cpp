#include "TestScript.h"
#include <iostream>

void TestScript::Update()
{
	std::cout << name << "\n";
}

void TestScript::Start()
{
	name = "Bum man";
}
