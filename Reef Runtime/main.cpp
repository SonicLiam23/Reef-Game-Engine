#include "RuntimeEngine.h"
int main()
{
	RuntimeEngine* engine = &RuntimeEngine::Get();
	engine->Start();
	while (engine->IsRunning())
	{
		engine->Update();
	}
	engine->End();
	return 0;
}