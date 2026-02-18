#pragma once
#include <string>
#include "EngineTypes.h"
class EngineState
{
public:
	virtual void Start(int windowScale = 100, std::string windowName = "Reef Engine") = 0;
	virtual void Update(ObjectVec& objects) = 0;
	virtual void End() = 0;
};

