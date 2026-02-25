#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include <string>
class Object;
class Script;

using ObjectUPtr = std::unique_ptr<Object>;
using ObjectVec = std::vector<ObjectUPtr>;

using ScriptVec = std::vector<Script*>;
using ObjectIDMap = std::unordered_map<std::string, size_t>;