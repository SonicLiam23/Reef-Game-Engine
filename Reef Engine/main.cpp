#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"
#include <SFML/System/Clock.hpp>
#include "Window.h"
#include "EditorWindow.h"
#include "EngineTypes.h"
#include "Object.h"

int main()
{

	EditorWindow window(100, "Reef Engine");
	window.Init();

	Object* testObj = new Object();
	ObjectVec objects;
	objects.push_back(testObj);

	testObj->SetTexture("Images/testimg.png");
	testObj->SetPosition({ 400, 200 });
	testObj->SetSize({ 5, 5 });
	
	while (window.Get()->isOpen())
	{
		testObj->SetPosition({ testObj->GetPosition().x + 1, testObj->GetPosition().y });
		window.Update(objects);
	}

	return 0;
}



int main_old()
{
#ifndef _WIN32
	std::cout << "Windows only bozo";
	return 0;
#endif // !WIN
	unsigned int windowScale = 100;
	sf::RenderWindow window(sf::VideoMode({ windowScale * 16, windowScale * 9 }), "Reef Engine", sf::Style::Titlebar | sf::Style::Close);
	
	sf::Vector2u windowSize = window.getSize();
	ImVec2 imguiSize(static_cast<float>(windowSize.x) / 10, static_cast<float>(windowSize.y));

	ImVec2 buttonSize(-FLT_MIN, 0.0f);

	window.setFramerateLimit(60);
	sf::Clock deltaClock;

	

#pragma region OBJECT_SETUP
	sf::Texture image("Images/testimg.png");
	image.setSmooth(false);

	sf::Sprite sprite(image);
	sprite.setPosition({ 480, 260 });
	sprite.setScale({ 5, 5 });
#pragma endregion


	ImGui::SFML::Init(window);
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(imguiSize);

	ImGuiWindowFlags dockspaceflags =
		ImGuiWindowFlags_NoDocking | 
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoBackground;

	while (window.isOpen())
	{
		windowSize = window.getSize();
		while (std::optional<sf::Event> eventOpt = window.pollEvent())
		{
			const sf::Event& event = *eventOpt;

			ImGui::SFML::ProcessEvent(window, event);

			if (event.is<sf::Event::Closed>())
			{
				window.close();
			}
		}

		ImGui::SFML::Update(window, deltaClock.restart());

#pragma region FULL_WINDOW_DOCKING_SPACE

		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::SetNextWindowSize({ static_cast<float>(windowSize.x), static_cast<float>(windowSize.y) });
		// Invisible window
		ImGui::Begin("DockSpaceWindow", nullptr, dockspaceflags);

		// Create the dockspace inside it
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);

		ImGui::End();
#pragma endregion

		ImGui::Begin("Tools Bar", nullptr);

		ImGui::Button("Add Image To Project", buttonSize);
		ImGui::Button("Tooltip button", buttonSize);
		if (ImGui::IsItemHovered(ImGuiHoveredFlags_Stationary))
			ImGui::SetTooltip("I am a tooltip requiring mouse to be stationary before activating.");

		ImGui::Text("WindowSize:");
		ImGui::SameLine();
		float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
		ImGui::PushItemFlag(ImGuiItemFlags_ButtonRepeat, true);
		if (ImGui::ArrowButton("+", ImGuiDir_Down)) { windowScale--; window.setSize({ windowScale * 16, windowScale * 9 }); }
		ImGui::SameLine(0.0f, spacing);
		if (ImGui::ArrowButton("-", ImGuiDir_Up)) { windowScale++; window.setSize({ windowScale * 16, windowScale * 9 }); }
		ImGui::PopItemFlag();

		ImGui::End();
		window.clear();
		// render objects here
		window.draw(sprite);

		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown(window);
	return 0;
}