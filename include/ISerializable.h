#pragma once
#include "json.hpp"

struct ISerializable {
    virtual ~ISerializable() = default;
    virtual nlohmann::json Serialize() const = 0;
    virtual void Deserialize(const nlohmann::json& j) = 0;
    virtual std::string GetTypeName() const = 0;
};

