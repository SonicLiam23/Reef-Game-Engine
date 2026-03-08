#include "MoveRight.h"
#include "Script.h"
#include "Vector2.h"

void MoveRight::Update()
{
	Math::Vector2 currPos = AttachedObject->GetPosition();
	currPos.x += moveAmt;
	AttachedObject->SetPosition(currPos);
}

void MoveRight::Start()
{
	moveAmt = 1;
}
