#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"
#include <SFML/System/Clock.hpp>
#include "Window.h"


int main()
{
#ifndef _WIN32
	std::cout << "Windows only bozo";
	return 0;
#endif // !WIN
	sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "Reef Engine v0", sf::Style::Titlebar | sf::Style::Close);
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

	while (window.isOpen())
	{
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
		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::SetNextWindowSize(imguiSize);
		ImGui::Begin(" ", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);

		ImGui::Button("Add Image To Project", buttonSize);
		ImGui::Button("Tooltip button", buttonSize);
		if (ImGui::IsItemHovered(ImGuiHoveredFlags_Stationary))
			ImGui::SetTooltip("I am a tooltip requiring mouse to be stationary before activating.");

		float value;
		

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