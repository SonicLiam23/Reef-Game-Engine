#pragma once
#include "EngineTypes.h"
#include "ISerializable.h"
#include "SerializableFactory.h"
#include "Script.h"

#ifdef GAME_EXPORTS
#define ENGINE_API __declspec(dllexport)
#define SCRIPT(ClassName) class __declspec(dllexport) ClassName : public Script
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
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(ClassName, __VA_ARGS__) \
    nlohmann::json Serialize() const override { return nlohmann::json(*this); } \
    void Deserialize(const nlohmann::json& j) override { from_json(j, *this); } \
    std::string GetTypeName() const override { return #ClassName; }