#pragma once
#include "EngineAPI.h"
#include "ISerializable.h"
#include "Object.h"
// user created scripts to be attached to objects will be inherited from this.
class ENGINE_API Script : public ISerializable
{
public:
	virtual void Update() = 0;
	virtual void Start() = 0;
	Object* AttachedObject;

	// to be honest, i dont know why this is needed, but given script is accessible in Game.dll, 
	// its something about if i call delete on a script elsewhere, it can cause errors/memory corruption
	virtual ~Script() = default;
};

