#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include <string>


class Object;
using ObjectUPtr = std::unique_ptr<Object>;
using ObjectVec = std::vector<ObjectUPtr>;

class Script;
using ScriptUPtr = std::unique_ptr<Script>;
using ScriptVec = std::vector<ScriptUPtr>;

using ObjectIDMap = std::unordered_map<std::string, size_t>;