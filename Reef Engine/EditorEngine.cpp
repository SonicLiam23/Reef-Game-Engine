#include "EditorEngine.h"
#include "EditorWindow.h"
#include <iostream>

EditorEngine::EditorEngine() : m_isInitialized(false), m_isRunning(false)
{
}

void EditorEngine::Start(int windowScale, std::string windowName)
{

	m_window = new EditorWindow(windowScale, windowName);
	m_window->Init();

	m_isRunning = true;
}

void EditorEngine::Update()
{
	m_window->Update(m_objects);
}

void EditorEngine::End()
{
	delete m_window;
}


///////////////////API///////////////////////


void EditorEngine::AddObject(Object* objToAdd)
{
	m_objects.push_back(objToAdd);
}

bool EditorEngine::IsRunning()
{
	return m_isRunning;
}
