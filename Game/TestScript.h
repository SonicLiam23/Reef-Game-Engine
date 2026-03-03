#pragma once
#include "GameExport.h"
class ENGINE_API TestScript : public Script
{
	int num;
	void Update() override;

	void Start() override;

	SERIALIZE(TestScript, num);
};

REGISTER_SERIALIZABLE(TestScript);

