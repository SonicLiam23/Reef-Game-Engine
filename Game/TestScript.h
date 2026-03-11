#pragma once
#include "GameExport.h"
#include <string>
class SCRIPT TestScript : public Script
{
	std::string name;
	int num;
	void Update() override;

	void Start() override;

	SERIALIZE(TestScript, name, num);
};

REGISTER_SERIALIZABLE(TestScript);