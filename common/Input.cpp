#include "Input.h"
#include "InputImpl.h"
#include "SFML/Window/Mouse.hpp"
#include "SFML/Graphics/RenderTarget.hpp"

sf::Time Input::doubleClickThreshold = sf::milliseconds(100);
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

// creates a click event and sets its clicked value to true if the button is currently being pressed, 
// and false otherwise. It also sets the position of the click event to the current mouse position
Input::ClickEvent Input::GetMouseButton(MouseButton button)
{
	ClickEvent event;
	
	// detect if button was pressed twice
	if (sf::Mouse::isButtonPressed(button))
	{
		sf::Time timeSinceLastClick = lastClickTime[(int)button].getElapsedTime();
		if (timeSinceLastClick < doubleClickThreshold)
		{
			event.clicked = DoubleClick;
		}
		else
		{
			event.clicked = SingleClick;
		}
		lastClickTime[(int)button].restart();
	}
	else
	{
		event.clicked = NoClick;
	}
	event.position = (Math::Vector2f)InputImpl::Get().GetRenderTarget()->mapPixelToCoords(sf::Mouse::getPosition());

	return event;
}
