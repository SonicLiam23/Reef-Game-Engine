#include "MoveRight.h"
#include "Script.h"
#include "Vector2.h"
#include "Input.h"
#include <iostream>
#include "Engine.h"

void MoveRight::Update()
{
	if (Input::GetKeyDown(Input::Key::D))
	{
		//moveAmt += 5;
	}

	Math::Vector2 currPos = AttachedObject->GetPosition();
	currPos.x += moveAmt;
	AttachedObject->SetPosition(currPos);
}

void MoveRight::Start()
{

}


