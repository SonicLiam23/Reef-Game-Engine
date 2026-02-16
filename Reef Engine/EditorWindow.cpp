#include "EditorWindow.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "Object.h"

void EditorWindow::Init()
{
	ImGui::SFML::Init(*m_window);

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

	SetImGuiElements();
	m_window->clear();
	ImGui::SFML::Render(*m_window); 

	for (Object*& object : objectsToRender)
	{
		m_window->draw(*object);
	}

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

	ImGui::Button("Add Image To Project", m_buttonSize);
	ImGui::Button("Tooltip button", m_buttonSize);
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_Stationary))
		ImGui::SetTooltip("I am a tooltip requiring mouse to be stationary before activating.");

	ImGui::Text("WindowSize:");
	ImGui::SameLine();
	float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
	ImGui::PushItemFlag(ImGuiItemFlags_ButtonRepeat, true);
	if (ImGui::ArrowButton("+", ImGuiDir_Down)) { m_windowScale--; m_window->setSize({ m_windowScale * 16, m_windowScale * 9 }); }
	ImGui::SameLine(0.0f, spacing);
	if (ImGui::ArrowButton("-", ImGuiDir_Up)) { m_windowScale++; m_window->setSize({ m_windowScale * 16, m_windowScale * 9 }); }
	ImGui::PopItemFlag();

	ImGui::End();
}
