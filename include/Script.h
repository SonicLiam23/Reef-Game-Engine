#pragma once
#include "EngineAPI.h"
#include "ISerializable.h"
#include "Object.h"
#include <vector>
#include <typeindex>

struct MemberInfo
{
	inline MemberInfo(std::string name, void* ptr, std::type_index type) : name(name), ptr(ptr), type(type) {}

	std::string name;
	void* ptr;              // pointer to the actual member
	std::type_index type;   // type information
};


// user created scripts to be attached to objects will be inherited from this.
class ENGINE_API Script : public ISerializable
{
public:
	virtual void Update() = 0;
	virtual void Start() = 0;
	virtual void REEF_ENGINE_INIT() = 0;
	Object* AttachedObject;

	// to be honest, i dont know why this is needed, but given script is accessible in Game.dll, 
	// its something about if i call delete on a script elsewhere, it can cause errors/memory corruption
	virtual ~Script() = default;

	// this is used for the editor to be able to reflect on the members of the script, so it can display them in the inspector and allow editing them.
	std::vector<MemberInfo> REEF_MEMBERS_REFLECTION;
};

