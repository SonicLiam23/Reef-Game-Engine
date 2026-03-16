#include "MoveRight.h"
#include "Script.h"
#include "Vector2.h"
#include "Input.h"
#include <iostream>

void MoveRight::Update()
{
	Math::Vector2 currPos = AttachedObject->GetPosition();
	currPos.x += moveAmt;
	AttachedObject->SetPosition(currPos);

	if (Input::GetKeyDown(Input::Key::D))
	{
		moveAmt == 10;
	}
}

void MoveRight::Start()
{

}


