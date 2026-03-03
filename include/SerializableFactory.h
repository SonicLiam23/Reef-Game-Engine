#pragma once
#include <unordered_map>
#include <functional>
#include <memory>
#include <string>
#include "EngineTypes.h"
#include "ISerializable.h"
#include "Script.h"
#include "EngineAPI.h"

class ENGINE_API SerializableFactory 
{
public:
    using Creator = std::function<ScriptUPtr()>;

    inline static SerializableFactory& Get() 
    {
        static SerializableFactory factory;
        return factory;
    }

    void RegisterType(const std::string& name, Creator c);

    ScriptUPtr Create(const std::string& name) const;

    const std::unordered_map<std::string, Creator>& GetRegistry() const;

private:
    std::unordered_map<std::string, Creator> m_registry;
};
