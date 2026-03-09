#include "InputImpl.h"
// this is used so the user cannot interact with certain things as part of the input system, such as "update key states" and "HandleKeyEvent"
// the Input.h is what the user will interact with

void InputImpl::init(sf::RenderTarget* target)
{
	m_currentRenderTarget = target;
}

sf::RenderTarget* InputImpl::GetRenderTarget()
{
	return m_currentRenderTarget;
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
	else
	{
		return;
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

InputImpl::InputImpl()
{
	for (int i = 0; i < sf::Keyboard::ScancodeCount; ++i)
	{
		m_keys[i] = NONE;
	}
}