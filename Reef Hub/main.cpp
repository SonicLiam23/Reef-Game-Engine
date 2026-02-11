#include <Windows.h>
#include <filesystem>
#include <shobjidl.h>
#include <commdlg.h> 
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

struct ProjectMetaData
{
    std::string projectName;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ProjectMetaData, projectName);


std::string OpenFileExlorer(DWORD flags)
{
    // Initialize COM
    CoInitialize(NULL);

    // Create the file dialog object
    IFileDialog* pfd = NULL;
    HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_PPV_ARGS(&pfd));

    if (SUCCEEDED(hr)) {
        // Set the options of the dialog (folder select mode)
        DWORD dwOptions;
        pfd->GetOptions(&dwOptions);
        pfd->SetOptions(dwOptions | flags);

        // Show the dialog
        hr = pfd->Show(NULL);

        // Get the selected folder path
        if (hr == S_OK) {
            // Get the file path
            IShellItem* pItem = NULL;
            hr = pfd->GetResult(&pItem);
            if (SUCCEEDED(hr)) {
                PWSTR pszFilePath = NULL;
                hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
                if (SUCCEEDED(hr)) {
                    // Convert wide string to a standard string
                    std::wstring wstr(pszFilePath);
                    std::string filePath(wstr.begin(), wstr.end());
                    CoTaskMemFree(pszFilePath);
                    pItem->Release();
                    pfd->Release();
                    CoUninitialize();
                    return filePath;
                }
            }
        }
        pfd->Release();
    }

    CoUninitialize();
    return "";  // Return empty string if canceled or failed
}

std::string GetFolderPath()
{
    return OpenFileExlorer(FOS_PICKFOLDERS);
}

std::string GetFilePath()
{
    return OpenFileExlorer(FOS_FILEMUSTEXIST);
}

std::filesystem::path GetExecutablePath()
{
    wchar_t buffer[MAX_PATH];
    GetModuleFileNameW(nullptr, buffer, MAX_PATH);
    return std::filesystem::path(buffer);
}

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

    std::filesystem::path templatePath = GetExecutablePath().parent_path() / "ProjectTemplate";
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
            currentPath = GetFolderPath();
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

