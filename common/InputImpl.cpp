#include "InputImpl.h"
// this is used so the user cannot interact with certain things as part of the input system, such as "update key states" and "HandleKeyEvent"
// the Input.h is what the user will interact with

void InputImpl::init(Window* target)
{
	m_window = target;
}

Window* InputImpl::GetWindow()
{
	return m_window;
}

void InputImpl::UpdateKeyStates()
{
	for (int i = 0; i < sf::Keyboard::ScancodeCount; ++i)
	{
		if (m_keys[i] == DOWN)
		{
			m_keys[i] = HELD;
		}
		else if (m_keys[i] == UP)
		{
			m_keys[i] = NONE;
		}
	}

	// same for mouse buttons
	for (int i = 0; i < sf::Mouse::ButtonCount; ++i)
	{
		if (m_mouseButtons[i] == DOWN)
		{
			m_mouseButtons[i] = HELD;
		}
		else if (m_mouseButtons[i] == UP)
		{
			m_mouseButtons[i] = NONE;
		}
	}
}

void InputImpl::HandleKeyEvent(const sf::Event& event)
{
	sf::Keyboard::Scancode scanCode;
	if (auto* key = event.getIf<sf::Event::KeyPressed>())
	{
		scanCode = key->scancode;
		int ind = (int)scanCode;

		if (m_keys[ind] == NONE)
		{
			m_keys[ind] = DOWN;
		}

	}
	else if (auto* key = event.getIf<sf::Event::KeyReleased>())
	{
		scanCode = key->scancode;
		int ind = (int)scanCode;
		 
		m_keys[ind] = UP; 
	}
	
	// handle mouse buttons
	sf::Mouse::Button button;
	if (auto* mouseButton = event.getIf<sf::Event::MouseButtonPressed>())
	{
		button = mouseButton->button;
		int ind = (int)button;
		if (m_mouseButtons[ind] == NONE)
		{
			m_mouseButtons[ind] = DOWN;
		}
	}
	else if (auto* mouseButton = event.getIf<sf::Event::MouseButtonReleased>())
	{
		button = mouseButton->button;
		int ind = (int)button;
		m_mouseButtons[ind] = UP;
	}
	

}

bool InputImpl::GetKeyDown(sf::Keyboard::Scancode key)
{
	return m_keys[(int)key] == DOWN;
}

bool InputImpl::GetKeyUp(sf::Keyboard::Scancode key)
{
	return m_keys[(int)key] == UP;
}

bool InputImpl::GetKeyHeld(sf::Keyboard::Scancode key)
{
	return m_keys[(int)key] == HELD;
}

bool InputImpl::GetMouseButtonDown(sf::Mouse::Button button)
{
	return m_mouseButtons[(int)button] == DOWN;
}

bool InputImpl::GetMouseButtonUp(sf::Mouse::Button button)
{
	return m_mouseButtons[(int)button] == UP;
}

bool InputImpl::GetMouseButtonHeld(sf::Mouse::Button button)
{
	return m_mouseButtons[(int)button] == HELD;
}

InputImpl::InputImpl()
{
	for (int i = 0; i < sf::Keyboard::ScancodeCount; ++i)
	{
		m_keys[i] = NONE;
	}
}