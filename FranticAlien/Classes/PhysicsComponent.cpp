#include "PhysicsComponent.h"
#include "GameObject.h"
#include "Level.h"

void PlayerPhysicsComponent::update(GameObject &gameObject, Level& level, float& delta)
{
    //log("%s", gameObject.getSomething());

	this->collisionDetection(gameObject, level, delta);
	//this->applyGravity(gameObject, level, delta);
}

void PlayerPhysicsComponent::applyGravity(GameObject &gameObject, Level& level, float& delta)
{
	//log("%s", gameObject.getSomething());

	float y = gameObject.getPositionY();

	delta += 6;

	y += delta * -1;

	gameObject.setPositionY(y);
}

void PlayerPhysicsComponent::collisionDetection(GameObject &gameObject, Level& level, float& delta)
{
	// Flags to specify what kind of collision has occurred
	bool contactX = false, contactYbottom = false, contactYtop = false;
		
	//log("%s", gameObject.getSomething());
	auto tileSize = level.getMap()->getTileSize();

	// calculate next offsets
	float objectNextX = gameObject.speedX * delta;
	float objectNextY = gameObject.speedY * delta;
	
	for (auto& object : level.getMap()->getChildren())
	{		
		auto layer = dynamic_cast<TMXLayer*>(object);

		// move to next object if layer is nullptr
		if (layer == nullptr)
			continue;
				
		// get the layer sizes
		auto layerSize = layer->getLayerSize();
		// calculate the co-ordinates in the layer
		int layerHeightPixels = layerSize.height * tileSize.height;
				
		// get current game object position
		auto objectPosition = layer->convertToNodeSpace(gameObject.getPosition());
			
		
		// calculate values for bounding box
		float objectOriginalX = objectPosition.x;
		float objectOriginalY = objectPosition.y;
		float objectWidth = gameObject.getContentSize().width;
		float objectHeight = gameObject.getContentSize().height;

		// create the bounding box with next offsets
		auto objectBoundingBox = Rect
		(
			std::min(objectOriginalX, objectOriginalX + objectNextX),
			std::min(objectOriginalY, objectOriginalY + objectNextY),
			objectWidth,
			objectHeight
		);

		// object min / max
		float objectLeft = objectBoundingBox.getMinX();
		float objectTop = objectBoundingBox.getMaxY();
		float objectRight = objectBoundingBox.getMaxX();
		float objectBottom = objectBoundingBox.getMinY();

		//
		int tileOrdinateX = objectBoundingBox.origin.x / tileSize.width;
		int tileOrdinateY = (layerHeightPixels - objectBoundingBox.origin.y) / tileSize.height; // need to flip y for cocos2d system

		// check if there is a tile in the layer		
		if (layer->getTileAt(Vec2(tileOrdinateX, tileOrdinateY)) == nullptr)
			continue;

		// No collisions found yet
		contactX = contactYbottom = contactYtop = false;

		// get the tiles bounding box
		auto tileBoundingBox = layer->getTileAt(Vec2(tileOrdinateX, tileOrdinateY))->getBoundingBox();

		// tile min / max
		float tileLeft = tileBoundingBox.getMinX();
		float tileTop = tileBoundingBox.getMaxY();
		float tileRight = tileBoundingBox.getMaxX();
		float tileBottom = tileBoundingBox.getMinY();

		// create the intersection rect of object and tile
		Rect intersection = Rect
		(
			std::max(objectBoundingBox.getMinX(), tileBoundingBox.getMinX()),
			std::max(objectBoundingBox.getMinY(), tileBoundingBox.getMinY()),
			0, // empty for width calc after
			0  // empty for height calc after
		);

		intersection.size.width = std::min(objectBoundingBox.getMaxX(), tileBoundingBox.getMaxX()) - intersection.getMinX();
		intersection.size.height = std::min(objectBoundingBox.getMaxY(), tileBoundingBox.getMaxY()) - intersection.getMinY();

		// intersection min / max
		float intersectionRectLeft = intersection.getMinX();
		float intersectionRectTop = intersection.getMaxY();
		float intersectionRectRight = intersection.getMaxX();
		float intersectionRectBottom = intersection.getMinY();

		float top = intersectionRectBottom - intersectionRectTop;
		float left = intersectionRectRight - intersectionRectLeft;

		if (top < 0)
		{
			objectOriginalY += top;
		
			gameObject.setPosition(layer->convertToWorldSpace(Vec2(objectOriginalX, objectOriginalY)));

			contactYbottom = true;
		}
	}

	if (contactYbottom)
	{
		gameObject.speedY = 0;
	}

	/*if (tile)
	{
	auto properties = level.getMap()->getPropertiesForGID(gid).asValueMap();
	auto collided = properties["Collidable"].asBool();

	if (collided)
	{
	log("WOOT!!!");
	if (tile->getBoundingBox().getMaxY() > position.y)
	{
	contactYbottom = true;
	}
	}
	}*/
}