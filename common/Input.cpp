#include "Input.h"
#include "InputImpl.h"

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
