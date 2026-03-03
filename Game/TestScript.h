#pragma once
#include "GameExport.h"
#include <string>
class ENGINE_API TestScript : public Script
{
	std::string name;
	void Update() override;

	void Start() override;

	SERIALIZE(TestScript, name);
};

REGISTER_SERIALIZABLE(TestScript);

