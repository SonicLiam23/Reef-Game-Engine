#pragma once
// user created scripts to be attached to objects will be inherited from this.
class Script
{
public:
	virtual void Update() = 0;
	virtual void Start() = 0;
};

