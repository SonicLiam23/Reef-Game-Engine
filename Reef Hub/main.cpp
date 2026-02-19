#include <string>
#include <sstream>
#include <vector>
#include <array>
#include <iostream>
#include <fstream>
#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"
#include <SFML/System/Clock.hpp>
#include "json.hpp"
#include "FileUtils.h"

struct ProjectMetaData
{
    std::string projectName;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ProjectMetaData, projectName);


void CreateProject(std::string name, std::string filepath, std::string* screenOutput)
{
    if (name.empty() || name[0] == ' ')
    {
        *screenOutput = "Please enter a valid project name";
        return;
    }
    else if (filepath.empty() || filepath[0] == ' ')
    {
        *screenOutput = "Please select a filepath.";
        return;
    }

    std::filesystem::path templatePath = FileUtils::GetExecutablePath().parent_path() / "ProjectTemplate";
    std::filesystem::path destinationPath = filepath;
    
    ProjectMetaData data;
    data.projectName = name;
    nlohmann::json jsonFile = data;

    std::ofstream file(templatePath / "ProjectTemplate" / "projectdata.json");
    if (!file.is_open()) 
    {
        std::cerr << "Failed to open file for writing\n";
        return;
    }
    file << jsonFile.dump(4);
    file.close();

    std::filesystem::copy(templatePath, destinationPath, std::filesystem::copy_options::recursive);
    std::filesystem::rename(destinationPath / "ProjectTemplate" / "ProjectTemplate", destinationPath / "ProjectTemplate" / name.c_str());
    std::filesystem::rename(destinationPath / "ProjectTemplate", destinationPath / name.c_str());
    
}

int main()
{
#ifndef _WIN32
    std::cout << "Windows only bozo";
    return 0;
#endif // !WIN


    sf::RenderWindow window(sf::VideoMode({540, 380}), "Reef Hub", sf::Style::Titlebar | sf::Style::Close);
    sf::Vector2u windowSize = window.getSize();
    ImVec2 imguiSize(static_cast<float>(windowSize.x), static_cast<float>(windowSize.y));

    window.setFramerateLimit(30);
    ImGui::SFML::Init(window);
    sf::Clock deltaClock;
    std::array<char, 51> projectName{};
    std::string currentPath = "";
    std::string extraInfo = "";
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
        ImGui::Text("Create new Project:");
        if (ImGui::Button("Select Folder"))
            currentPath = FileUtils::GetFolderPath();
        ImGui::TextWrapped(currentPath.c_str(), 123);
        ImGui::InputText("Project Name", projectName.data(), projectName.size());
        if (ImGui::Button("Create Project"))
            CreateProject(std::string(projectName.data()), currentPath, &extraInfo);
        ImGui::Text(extraInfo.c_str(), 123);
        ImGui::Text("=========");
        ImGui::Button("Load project from file");
        ImGui::Text("\nReef Hub pre-alpha", 100);
        ImGui::End();

        window.clear();
        ImGui::SFML::Render(window);
        window.display();
    }

    
    
    ImGui::SFML::Shutdown(window);

	return 0;
}

