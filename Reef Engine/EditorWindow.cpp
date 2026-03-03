#include "EditorWindow.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_internal.h"
#include "Object.h"
#include "EditorEngine.h"
#include "Rect.h"
#include "FileUtils.h"
#include <iostream>
#include "SerializableFactory.h"

void HelpMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::BeginItemTooltip())
	{
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

void EditorWindow::Start(EditorEngine* engine)
{
	m_attachedEngine = engine;

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

	m_viewport.parent = this;
	
	m_selectedObjectThisFrame = false;
}

void EditorWindow::Update(ObjectVec& objectsToRender)
{
	while (std::optional<sf::Event> eventOpt = m_window->pollEvent())
	{
		const sf::Event& event = *eventOpt;

		ImGui::SFML::ProcessEvent(*m_window, event);

		if (event.is<sf::Event::Closed>())
		{
			m_attachedEngine->End();
			m_window->close();
		}
	}

	m_viewPortTex->clear();
	for (ObjectUPtr& objectUptr: objectsToRender)
	{
		Object* object = objectUptr.get();
		sf::RectangleShape outline = m_outlines[object];
		outline.setFillColor(sf::Color::Transparent);
		if (object == m_selectedObject)
		{
			outline.setOutlineColor(sf::Color::Red);
		}
		else
		{
			outline.setOutlineColor(sf::Color::Yellow);
		}
		
		outline.setOutlineThickness(1.7f);
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

	m_selectedObjectThisFrame = false;
}

EditorWindow::Viewport* EditorWindow::GetViewport()
{
	return &m_viewport;
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

#pragma region TOOLS_BAR
	ImGui::Begin("Tools Bar", nullptr);

	ImGui::BringWindowToDisplayFront(ImGui::GetCurrentWindow());

	if (ImGui::Button("Add Object", m_buttonSize))
	{
		m_attachedEngine->AddObject();
	}
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_Stationary))
		ImGui::SetTooltip("Adds an empty square to the screen.");

#pragma region SELECTING_OBJECT
	if (m_selectedObject)
	{
		if (m_selectedObjectThisFrame)
		{
			m_inputID = m_selectedObject->GetID();
		}
		ImGui::Text("Object:"); ImGui::SameLine();
		ImGui::Text(m_selectedObject->name.c_str());


		ImGui::InputText("Name", &m_selectedObject->name);

		ImGui::InputText("ID", &m_inputID);
		if (ImGui::Button("Set ID", m_buttonSize))
		{
			m_selectedObject->SetID(m_inputID);
			// update text box with new ID (input validation may change it)
			m_inputID = m_selectedObject->GetID();
		}
		ImGui::SameLine(); HelpMarker("IDs Must be unique");


		Math::Rect objRect = m_selectedObject->GetRect();

		ImGui::DragFloat2("Position", objRect.PositionData());
		ImGui::DragFloat2("Size", objRect.SizeData());

		m_selectedObject->SetPosition(objRect.position);
		m_selectedObject->SetSize(objRect.size);

		if (ImGui::Button("Add Image", m_buttonSize))
		{
			m_selectedObject->SetTexture(FileUtils::GetImageAndCopyToProject());
			m_selectedObject->SetSize(objRect.size);
		}

		if (ImGui::BeginCombo("Add Script", "Select Script"))
		{
			for (auto& [name, _] : SerializableFactory::Get().GetRegistry())
			{
				if (ImGui::Selectable(name.c_str()))
				{
					auto script = SerializableFactory::Get().Create(name);
					m_selectedObject->AddScript(std::move(script));
				}
			}

			ImGui::EndCombo();
		}


		if (ImGui::Button("Delete Object", m_buttonSize))
		{
			m_selectedObject->Destroy();
		}
	}
#pragma endregion



	ImGui::Text("WindowSize:");
	ImGui::SameLine();
	float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
	ImGui::PushItemFlag(ImGuiItemFlags_ButtonRepeat, true);
	if (ImGui::ArrowButton("+", ImGuiDir_Down)) { m_windowScale--; m_window->setSize({ m_windowScale * 16, m_windowScale * 9 }); }
	ImGui::SameLine(0.0f, spacing);
	if (ImGui::ArrowButton("-", ImGuiDir_Up)) { m_windowScale++; m_window->setSize({ m_windowScale * 16, m_windowScale * 9 }); }
	ImGui::PopItemFlag();
	ImGui::End();
#pragma endregion



#pragma region VIEWPORT
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::Begin("Viewport", nullptr, m_viewportFlags);

	ImVec2 viewportSize = ImGui::GetContentRegionAvail();
	ImGui::Image(m_viewPortTex->getTexture().getNativeHandle(), viewportSize, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

	// set the viewport info
	m_viewport.position = ImGui::GetItemRectMin();
	m_viewport.size = ImGui::GetItemRectSize();
	m_viewport.mouseHovered = ImGui::IsItemHovered();

	ImGui::End();
	ImGui::PopStyleVar(2);
#pragma endregion


}

void EditorWindow::SetSelectedObject(Object* newSelected)
{
	m_selectedObject = newSelected;
	m_selectedObjectThisFrame = true;
}


//////////////////VIEWPORT////////////////

std::optional<Math::Vector2f> EditorWindow::Viewport::GetMousePos()
{
	if (!mouseHovered)
	{
		return std::nullopt;
	}

	ImVec2 mousePos = ImGui::GetMousePos();

	float localX = mousePos.x - position.x;
	float localY = mousePos.y - position.y;

	if (localX < 0.f || localY < 0.f ||
		localX > size.x || localY > size.y)
		return std::nullopt;

	float renderWidth = (float)(parent->m_viewPortTex->getSize().x);
	float renderHeight = (float)(parent->m_viewPortTex->getSize().y);

	float scaleX = renderWidth / size.x;
	float scaleY = renderHeight / size.y;

	localX *= scaleX;
	localY *= scaleY;

	// Convert pixel space -> world space using SFML view
	sf::Vector2f world = parent->m_window->mapPixelToCoords(sf::Vector2i(static_cast<int>(localX), static_cast<int>(localY)));

	return Math::Vector2f(world.x, world.y);
}