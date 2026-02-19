#include <Windows.h>
#include <filesystem>
#include <shobjidl.h>
#include <commdlg.h> 
#include <string>


namespace
{
    COMDLG_FILTERSPEC fileTypes[] =
    {
        { L"All Files", L"*.*" },
        { L"Image Files", L"*.png;*.jpg;*.jpeg;*.bmp" },
        { L"PNG Files", L"*.png" }
    };

    enum FileSelectFilter
    {
        ALL = 0,
        IMG = 1,
        PNG = 2
    };
}

namespace FileUtils
{


    std::string OpenFileExlorer(DWORD flags, FileSelectFilter filter = ALL)
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

            pfd->SetFileTypes(3, fileTypes);
            pfd->SetFileTypeIndex(filter); // default to first filter

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

    std::string GetImageAndCopyToProject()
    {
        const std::string filePath = OpenFileExlorer(PNG);
        if (filePath.empty())
            return "";
#ifdef _DEBUG
        std::filesystem::path engineDest = std::filesystem::path(IMAGES_PATH_PROJECT) / std::filesystem::path(filePath).filename();
        std::filesystem::create_directories(engineDest.parent_path());
        std::filesystem::copy_file(filePath, engineDest, std::filesystem::copy_options::overwrite_existing);
#endif

        std::filesystem::path exeDest = GetExecutablePath().parent_path() / "Images" / std::filesystem::path(filePath).filename();
        std::filesystem::create_directories(exeDest.parent_path());
        std::filesystem::copy_file(filePath, exeDest, std::filesystem::copy_options::overwrite_existing);

        return filePath;
    }


}
