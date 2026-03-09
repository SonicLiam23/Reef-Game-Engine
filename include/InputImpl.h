#pragma once
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Mouse.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "EngineAPI.h"
#include "Vector2.h"
#include "Input.h"
#include "Window.h"
class ENGINE_API InputImpl
{
public:

	struct ClickEvent
	{
		bool clicked;
		Math::Vector2f position;
	};

	inline static InputImpl& Get()
	{
		static InputImpl instance;
		return instance;
	}

	void init(sf::RenderTarget* target);

	sf::RenderTarget* GetRenderTarget();
	void UpdateKeyStates();
	void HandleKeyEvent(const sf::Event& event);

	// API
	bool GetKeyDown(sf::Keyboard::Scancode key);
	bool GetKeyUp(sf::Keyboard::Scancode key);
	bool GetKeyHeld(sf::Keyboard::Scancode key);

private:
	enum KeyState
	{
		NONE,
		DOWN,
		HELD,
		UP
	};

	KeyState m_keys[sf::Keyboard::ScancodeCount];
	InputImpl();
	sf::RenderTarget* m_currentRenderTarget;
};