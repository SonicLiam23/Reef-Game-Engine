#pragma once
#include <vector>
#include <memory>
class Object;
class Script;

using ObjectUPtr = std::unique_ptr<Object>;
using ObjectVec = std::vector<ObjectUPtr>;

using ScriptVec = std::vector<Script*>;