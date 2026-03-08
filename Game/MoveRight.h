#pragma once
#include "GameExport.h"
class SCRIPT MoveRight : public Script
{
	int moveAmt;

	void Update() override;
	void Start() override;

	SERIALIZE(MoveRight, moveAmt);
};

REGISTER_SERIALIZABLE(MoveRight);
