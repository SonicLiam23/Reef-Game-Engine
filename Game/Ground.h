#pragma once
#include "GameExport.h"
class SCRIPT Ground :
    public Script
{
public:
	char _;

	void Start() override;
	void Update() override;

	SERIALIZE(Ground, _);
};

REGISTER_SERIALIZABLE(Ground);

