#include "EditorEngine.h"
int main()
{
	EditorEngine* engine = &EditorEngine::Get();
	engine->Start();
	while (engine->IsRunning())
	{
		engine->Update();
	}
	engine->End();
	return 0;
}