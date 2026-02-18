#include "EditorWindow.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_internal.h"
#include "Object.h"

#include <iostream>

void EditorWindow::Init()
{
	ImGui::SFML::Init(*m_window);

	m_viewPortTex = new sf::RenderTexture(m_window->getSize());

	m_window->setFramerateLimit(60);

	m_buttonSize = { -FLT_MIN, 0.0f };

	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(m_window->getSize());

	m_dockspaceflags =
		ImGuiWindowFlags_NoDocking |
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoBackground;

	m_viewportFlags =
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoScrollWithMouse |
		ImGuiWindowFlags_NoBringToFrontOnFocus;

	m_windowScale = 100;
}

void EditorWindow::Update(ObjectVec& objectsToRender)
{
	while (std::optional<sf::Event> eventOpt = m_window->pollEvent())
	{
		const sf::Event& event = *eventOpt;

		ImGui::SFML::ProcessEvent(*m_window, event);

		if (event.is<sf::Event::Closed>())
		{
			m_window->close();
		}
	}

	m_viewPortTex->clear();
	for (Object*& object : objectsToRender)
	{

		sf::RectangleShape outline = m_outlines[object];
		outline.setFillColor(sf::Color::Transparent);
		outline.setOutlineColor(sf::Color::Yellow);
		outline.setOutlineThickness(1);
		outline.setSize(object->GetSize());
		outline.setPosition(object->GetPosition());


		m_viewPortTex->draw(outline);
		m_viewPortTex->draw(*object);
	}
	m_viewPortTex->display();


	SetImGuiElements();

	m_window->clear();
	ImGui::SFML::Render(*m_window);
	m_window->display();

}

void EditorWindow::SetImGuiElements()
{
	ImGui::SFML::Update(*m_window, deltaClock.restart());

#pragma region FULL_WINDOW_DOCKING_SPACE

	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(m_window->getSize());
	// Invisible window
	ImGui::Begin("DockSpaceWindow", nullptr, m_dockspaceflags);

	// Create the dockspace inside it
	ImGuiID dockspace_id = ImGui::GetID("DockSpace");
	ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);

	ImGui::End();
#pragma endregion

	ImGui::Begin("Tools Bar", nullptr);

	ImGui::BringWindowToDisplayFront(ImGui::GetCurrentWindow());

	if (ImGui::Button("Add Object", m_buttonSize))
	{
		std::cout << "Pressed\n";
	}
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_Stationary))
		ImGui::SetTooltip("Adds an empty square to the screen.");

	ImGui::Text("WindowSize:");
	ImGui::SameLine();
	float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
	ImGui::PushItemFlag(ImGuiItemFlags_ButtonRepeat, true);
	if (ImGui::ArrowButton("+", ImGuiDir_Down)) { m_windowScale--; m_window->setSize({ m_windowScale * 16, m_windowScale * 9 }); }
	ImGui::SameLine(0.0f, spacing);
	if (ImGui::ArrowButton("-", ImGuiDir_Up)) { m_windowScale++; m_window->setSize({ m_windowScale * 16, m_windowScale * 9 }); }
	ImGui::PopItemFlag();
	ImGui::End();

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::Begin("Viewport", nullptr, m_viewportFlags);

	ImVec2 viewportSize = ImGui::GetContentRegionAvail();
	ImGui::Image(m_viewPortTex->getTexture().getNativeHandle(), viewportSize, ImVec2{0, 1}, ImVec2{1, 0});
	
	ImGui::End();
	ImGui::PopStyleVar(2);
}
