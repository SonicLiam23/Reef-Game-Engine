#pragma once
#include "Vector2.h"

class Window;

class Engine
{
public:
	Engine();
	void Start();
	void Init(Math::Vector2u windowSize);
	void Update();

private:
	bool m_running;
	bool m_initialized;

};

