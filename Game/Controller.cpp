#include "Controller.h"
#include "Input.h"
#include "Engine.h"
void Controller::Update()
{
	Math::Vector2f currPos = AttachedObject->GetPosition();
	if (Input::GetKeyHeld(Input::Key::W))
	{
		currPos.y -= 5;
	}
	else if (Input::GetKeyHeld(Input::Key::S))
	{
		currPos.y += 5;
	}
	if (Input::GetKeyHeld(Input::Key::A))
	{
		currPos.x -= 5;
	}
	else if (Input::GetKeyHeld(Input::Key::D))
	{
		currPos.x += 5;
	}
	AttachedObject->SetPosition(currPos);
}

void Controller::Start()
{
	//if(!Engine::Get().CameraAttachedObject)
		//Engine::Get().AttachCameraToObject(AttachedObject);
}