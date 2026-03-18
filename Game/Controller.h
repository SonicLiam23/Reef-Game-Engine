#pragma once
#include "GameExport.h"
class SCRIPT Controller :
    public Script
{
    char _;
    void Update() override;

    void Start() override;

public:
	~Controller() = default; 
	template<typename BasicJsonType, nlohmann::detail::enable_if_t<nlohmann::detail::is_basic_json<BasicJsonType>::value, int> = 0> 
	
	friend void to_json(BasicJsonType& nlohmann_json_j, const Controller& nlohmann_json_t) 
	{
		nlohmann_json_j["_"] = nlohmann_json_t._;
	} 
	template<typename BasicJsonType, nlohmann::detail::enable_if_t<nlohmann::detail::is_basic_json<BasicJsonType>::value, int> = 0>
	
	friend void from_json(const BasicJsonType& nlohmann_json_j, Controller& nlohmann_json_t)
	{
		nlohmann_json_j.at("_").get_to(nlohmann_json_t._);
	}
	
	nlohmann::json Serialize() const override	
	{
		return nlohmann::json(*this);
	}
	
	void Deserialize(const nlohmann::json& j) override 
	{
		try {
			from_json(j, *this);
		}
		catch (const std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	} 
	
	std::string GetTypeName() const override 
	{
		return "Controller";
	}
	
	void REEF_ENGINE_INIT() override 
	{
		CreateMemberInfo(REEF_MEMBERS_REFLECTION, "_", _);
	};

};

struct Controller_Registrator {
    Controller_Registrator() {
        SerializableFactory::Get().RegisterType("Controller", []() { return std::make_unique<Controller>(); });
    }
}; inline static Controller_Registrator global_Controller_registrator;;