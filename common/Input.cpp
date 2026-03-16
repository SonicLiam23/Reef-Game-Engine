#include "Input.h"
#include "InputImpl.h"
#include "SFML/Window/Mouse.hpp"
#include "SFML/Graphics/RenderTarget.hpp"


sf::Time Input::doubleClickThreshold = sf::milliseconds(200);
sf::Clock Input::lastClickTime[(int)sf::Mouse::Button::Count];

bool Input::GetKeyDown(Input::Key key)
{
	return InputImpl::Get().GetKeyDown(key);
}

bool Input::GetKeyUp(Input::Key key)
{
	return InputImpl::Get().GetKeyUp(key);
}

bool Input::GetKeyHeld(Input::Key key)
{
	return InputImpl::Get().GetKeyHeld(key);
}

bool Input::GetMouseButtonDown(MouseButton button)
{
	if (InputImpl::Get().GetMouseButtonDown(button))
	{
		sf::Time timeSinceLastClick = lastClickTime[(int)button].restart();
		return true;
	}
	return false;
}

bool Input::GetMouseButtonUp(MouseButton button)
{
	return InputImpl::Get().GetMouseButtonUp(button);
}

bool Input::GetMouseButtonHeld(MouseButton button)
{
	return InputImpl::Get().GetMouseButtonHeld(button);
}

// creates a click event and sets its clicked value to true if the button is currently being pressed, 
// and false otherwise. It also sets the position of the click event to the current mouse position
Input::ClickEvent Input::GetMouseButtonInfo(MouseButton button)
{
	ClickEvent event;
	
	// detect if button was pressed twice
	if (InputImpl::Get().GetMouseButtonDown(button))
	{
		sf::Time timeSinceLastClick = lastClickTime[(int)button].restart();
		if (timeSinceLastClick < doubleClickThreshold)
		{
			event.clickType = DoubleClick;
		}
		else
		{
			event.clickType = SingleClick;
		}
	}
	else
	{
		if (InputImpl::Get().GetMouseButtonHeld(button))
		{
			event.clickType = Held;
		}
		else if (InputImpl::Get().GetMouseButtonUp(button))
		{
			event.clickType = Up;
		}
		else
		{
			event.clickType = NoClick;
		}
	}
	event.position = InputImpl::Get().GetWindow()->ConvertScreenPointToWorldCoords((Math::Vector2i)sf::Mouse::getPosition());

	return event;
}
