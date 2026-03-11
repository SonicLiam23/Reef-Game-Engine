#pragma once
#include "EngineTypes.h"
#include "ISerializable.h"
#include "SerializableFactory.h"
#include "Script.h"
#include <iostream>
#include <string>
#include <sstream>
#include <typeindex>

template <typename T>
inline MemberInfo MakeMemberInfo(std::string name, T& var)
{
    return MemberInfo(name, &var, typeid(T));
}

template<typename... Args>
inline void CreateMemberInfo(std::vector<MemberInfo>& vecToFill, const char* namesCstr, Args&& ... args)
{
    std::string names(namesCstr);
    std::istringstream ss(names);
    std::vector<std::string> nameList;
    std::string name;

    // Split names by comma
    while (std::getline(ss, name, ','))
    {
        // Remove leading/trailing spaces
        size_t start = name.find_first_not_of(' ');
        size_t end = name.find_last_not_of(' ');
        nameList.push_back(name.substr(start, end - start + 1));
    }

    // Helper lambda to iterate both packs together
    size_t i = 0;
    (vecToFill.push_back(MakeMemberInfo(nameList[i++], args)), ...);
}

#ifdef GAME_EXPORTS
#define SCRIPT __declspec(dllexport)
#else
#define SCRIPT __declspec(dllimport)
#endif


// in game.dll, included in all scripts.
#define REGISTER_SERIALIZABLE(ClassName) \
struct ClassName##_Registrator { \
    ClassName##_Registrator() { \
        SerializableFactory::Get().RegisterType(#ClassName, [](){ \
            return std::make_unique<ClassName>(); \
        }); \
    } \
}; \
inline static ClassName##_Registrator global_##ClassName##_registrator;

// REQUIRES AT LEAST 1 FIELD TO SERIALIZE
#define SERIALIZE(ClassName, ...) \
    public: \
    ~ClassName() = default; \
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(ClassName, __VA_ARGS__) \
    nlohmann::json Serialize() const override { return nlohmann::json(*this); } \
    void Deserialize(const nlohmann::json& j) override { try { from_json(j, *this); } catch (const std::exception& e) { std::cout << e.what() << std::endl; } } \
    std::string GetTypeName() const override { return #ClassName; } \
    void REEF_ENGINE_INIT() override { CreateMemberInfo(REEF_MEMBERS_REFLECTION, #__VA_ARGS__, __VA_ARGS__); }