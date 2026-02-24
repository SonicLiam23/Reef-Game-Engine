
#include <json.hpp>
#include <string>

struct ISerializable {
    virtual ~ISerializable() = default;
    virtual nlohmann::json serialize() const = 0;
    virtual void deserialize(const nlohmann::json& j) = 0;
    virtual std::string type_name() const = 0;
};

#include <unordered_map>
#include <functional>
#include <memory>

using SerializablePtr = std::unique_ptr<ISerializable>;

class SerializableFactory {
public:
    using Creator = std::function<SerializablePtr()>;

    static SerializableFactory& instance() {
        static SerializableFactory factory;
        return factory;
    }

    void register_type(const std::string& name, Creator c) {
        registry[name] = c;
    }

    SerializablePtr create(const std::string& name) const {
        auto it = registry.find(name);
        if (it != registry.end()) return it->second();
        return nullptr;
    }

private:
    std::unordered_map<std::string, Creator> registry;
};

#define REGISTER_SERIALIZABLE(ClassName) \
struct ClassName##_Registrator { \
    ClassName##_Registrator() { \
        SerializableFactory::instance().register_type(#ClassName, [](){ \
            return std::make_unique<ClassName>(); \
        }); \
    } \
}; \
inline static ClassName##_Registrator global_##ClassName##_registrator;

#define SERIALIZE(ClassName, ...) \
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(ClassName, __VA_ARGS__) \
    nlohmann::json serialize() const override { return nlohmann::json(*this); } \
    void deserialize(const nlohmann::json& j) override { *this = j.get<ClassName>(); } \
    std::string type_name() const override { return #ClassName; }

class MyClass : public ISerializable {
public:
    int num;
    std::string name;

    SERIALIZE(MyClass, num, name)  // injects JSON + ISerializable

};

REGISTER_SERIALIZABLE(MyClass)