#pragma once
#include "imgui.h"
#include "imgui_stdlib.h"
#include <string>
#include <vector>
#include "Vector2.h"
#include "Rect.h"
#include "Script.h"
#include <typeindex>


namespace ImGui
{

	inline void DrawMember(std::string& name)
	{
		ImGui::Text(name.c_str());
	}

	inline void DrawMember(std::string& member, std::string& name)
	{
		ImGui::InputText(name.c_str(), &member);
	}
	inline void DrawMember(float& member, std::string& name)
	{
		ImGui::DragFloat(name.c_str(), &member);
	}
	inline void DrawMember(int&
		member, std::string& name)
	{
		ImGui::DragInt(name.c_str(), &member);
	}

	// bool
	inline void DrawMember(bool& member, std::string& name)
	{
		ImGui::Checkbox(name.c_str(), &member);
	}

	// Vector2
	inline void DrawMember(Math::Vector2f& member, std::string& name)
	{
		ImGui::DragFloat2(name.c_str(), &member.x);
	}

	inline void DrawMember(Math::Vector2i& member, std::string& name)
	{
		ImGui::DragInt2(name.c_str(), &member.x);
	}

	// rect

	inline void DrawMember(Math::Rect& member, std::string& name)
	{
		ImGui::DragFloat2((name + " Position").c_str(), member.PositionData());
		ImGui::DragFloat2((name + " Size").c_str(), member.SizeData());
	}

	void DrawMemberProxy(MemberInfo& member)
	{
		if (member.type == typeid(std::string))
			DrawMember(*static_cast<std::string*>(member.ptr), member.name);
		else if (member.type == typeid(int))
			DrawMember(*static_cast<int*>(member.ptr), member.name);
		else if (member.type == typeid(float))
			DrawMember(*static_cast<float*>(member.ptr), member.name);
		else if (member.type == typeid(bool))
			DrawMember(*static_cast<bool*>(member.ptr), member.name);
		else if (member.type == typeid(Math::Vector2f))
			DrawMember(*static_cast<Math::Vector2f*>(member.ptr), member.name);
		else if (member.type == typeid(Math::Vector2i))
			DrawMember(*static_cast<Math::Vector2i*>(member.ptr), member.name);
		else if (member.type == typeid(Math::Rect))
			DrawMember(*static_cast<Math::Rect*>(member.ptr), member.name);
		else
			DrawMember(member.name);
	}
}