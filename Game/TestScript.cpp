#include "TestScript.h"
#include <iostream>
#include "Input.h"
#include "RuntimeEngine.h"

void TestScript::Update()
{
	
	Input::ClickEvent clickEvent = Input::GetMouseButtonInfo(Input::MouseButton::Left);

	if (clickEvent.clickType == Input::SingleClick)
	{
		std::cout << "Mouse clicked at position: " << clickEvent.position.x << ", " << clickEvent.position.y << "\n";

		if (AttachedObject->IsColliding(clickEvent.position))
		{
			std::cout << "Object was clicked!\n";
		}
	}
}

void TestScript::Start()
{
	name = "test passed";
}
