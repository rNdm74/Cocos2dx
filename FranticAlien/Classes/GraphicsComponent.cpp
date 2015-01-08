#include "AppGlobal.h"
#include "Box2D.h"
#include "Constants.h"
#include "GameObject.h"
#include "GraphicsComponent.h"

void PlayerGraphicsComponent::update(GameObject &gameObject)
{
	auto bodyPos = gameObject.getBody()->GetPosition();

	/*gameObject.setPosition
	(
		Vec2(bodyPos.x * kPixelsPerMeter, bodyPos.y * kPixelsPerMeter)
	);*/
}