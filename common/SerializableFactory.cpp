#include "SerializableFactory.h"

ScriptUPtr SerializableFactory::Create(const std::string& name) const
{
    auto it = m_registry.find(name);
    if (it != m_registry.end()) return it->second();
    return nullptr;
}

void SerializableFactory::RegisterType(const std::string& name, Creator c)
{
    m_registry[name] = c;
}


const std::unordered_map<std::string, SerializableFactory::Creator>& SerializableFactory::GetRegistry() const
{
    return m_registry;
}