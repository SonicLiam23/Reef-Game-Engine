#pragma once
#include "EngineAPI.h"
#include "Vector2.h"
class Object;
struct ENGINE_API Camera
{
	Camera();
	~Camera() = default;

	void AttachToObject(Object* obj);
	void Detach();

	void SetPosition(Math::Vector2f newPos);
	void SetPosition(Object* obj); // set position to the middle of the object once, do not follow if object moves

	const Math::Vector2f& GetPosition() const;
	

	// maybe a zoom level in the future, but not sure how to implement


private:
	Object* m_attachedObject;
	bool m_isAttached; // maybe if m_attachedObject is null then its not attached, but this is more explicit
	Math::Vector2f m_position; // the actual position of the camera, used when not attached to an object

	// position is a pointer so it can either point to m_position or the middle of the attached object, so the camera can follow the object without needing to update the position every frame
	const Math::Vector2f* m_realPosition;
};

