#include "EngineWindow.h"
#include "imgui.h"
#include "imgui-SFML.h"

void EngineWindow::Init()
{
	m_window->setFramerateLimit(60);

	sf::Vector2u windowSize = m_window->getSize();

	m_imGuiWindowSize = { static_cast<float>(windowSize.x) / 10, static_cast<float>(windowSize.y) };
	m_buttonSize = { -FLT_MIN, 0.0f };
}

void EngineWindow::Update(ObjectVec objectsToRender)
{
	SetImGuiElements();
	m_window->clear();
	ImGui::SFML::Render(*m_window); 

	// render objects here.

	m_window->display();
}

void EngineWindow::SetImGuiElements()
{
	ImGui::SFML::Update(*m_window, deltaClock.restart());
	ImGui::SetNextWindowPos({ 0, 0 });
	ImGui::SetNextWindowSize(m_imGuiWindowSize);

	ImGui::Begin(" ", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);

	ImGui::Button("Add Image To Project", m_buttonSize);
	ImGui::Button("Tooltip button", m_buttonSize);
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_Stationary))
		ImGui::SetTooltip("I am a tooltip requiring mouse to be stationary before activating.");


	ImGui::End();
}
