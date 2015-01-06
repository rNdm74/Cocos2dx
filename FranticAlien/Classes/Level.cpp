#include "Level.h"
#include "GameObject.h"

void Level::loadMap(const char* mapname){

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Vec2 mapOrigin = Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);

	map = TMXTiledMap::create(mapname);
	map->retain();

	map->setAnchorPoint(Vec2(0.5, 0.5));
	map->setPosition(mapOrigin);

	for (const auto& child : map->getChildren())
	{
		static_cast<SpriteBatchNode*>(child)->getTexture()->setAntiAliasTexParameters();

		//worldObjectBoundingBoxes.push_back(child->getBoundingBox());
	}

	setupResources();
}

TMXTiledMap* Level::getMap(){
	return map;
}

Level::Level()
{
	
}

Level::~Level(void)
{
	map->release();
}

void Level::setupResources()
{

	typedef enum { Rectangle, Ellipse } ShapeType;

	typedef struct {
		int width;
		int height;
		ShapeType shape;
		float scaleX;
		float scaleY;
		Vec2 scalePoint;
		float skewAngleX;
		float skewAngleY;
		Vec2 skewPoint;
		float rotAngle;
		Vec2 rotPoint;
		int topLeftX;
		int topLeftY;
	} ObjectDefinition;

	worldObjects = map->getChildren();

	worldObjectCount = 0;
		
	

	for (auto& object : worldObjects)
	{
		// is this map child a tile layer?
		auto layer = dynamic_cast<TMXLayer*>(object);

		auto layerName = layer->getLayerName();

		bool isCollidable = layerName != "4" && layerName != "5";


		//auto 
		if (layer != nullptr && isCollidable)
		{						
			addWorldObjects(*layer);
		}
	}
}

void Level::addWorldObjects(TMXLayer& layer)
{
	Size layerSize = layer.getLayerSize();

	for (int y = 0; y < layerSize.height; y++)
	{
		for (int x = 0; x < layerSize.width; x++)
		{			
			auto tileSprite = layer.getTileAt(Vec2(x, y));
						
			if (tileSprite)
			{
				auto anchor = tileSprite->getAnchorPoint();
				worldObjectCount++;

				worldObjectBoundingBoxes.push_back(tileSprite->getBoundingBox());							
			}
		}
	}
}

void Level::checkCollisions(float& delta, GameObject& player)
{
	for (auto& object : this->map->getChildren())
	{
		// is this map child a tile layer?
		auto layer = dynamic_cast<TMXLayer*>(object);

		if (layer != nullptr)
		{
			this->checkTiles(delta, *layer, player);
		}			
	}
}
void Level::checkTiles(float& delta, TMXLayer& layer, GameObject& player)
{
	bool collisionDetected = false;


	// create all the rectangular fixtures for each tile
	Size layerSize = layer.getLayerSize();

	for (int y = 0; y < layerSize.height; y++)
	{
		for (int x = 0; x < layerSize.width; x++)
		{
			// create a fixture if this tile has a sprite
			auto tileSprite = layer.getTileAt(Vec2(x, y));
			int gid = layer.tileGIDAt(Vec2(x, y));

			if (tileSprite)
			{
				// Get the tile bounds
				auto tilePos = tileSprite->getPosition();
				Rect tileBounds = tileSprite->getBoundingBox();

				// Get the player bounds relative to layer co-ordinates
				auto playerPos = layer.convertToNodeSpace(player.getPosition());
				auto playerSize = player.getContentSize();

				float playerX = playerPos.x;
				float playerY = playerPos.y;
				float playerW = playerSize.width;
				float playerH = playerSize.height / 2;

				// 
				float nextMoveX = player.speedX * delta;
				float nextMoveY = player.speedY * delta;

				// Create new boundsRect for collsion check
				Rect playerBounds = Rect
				(
					std::min(playerX, playerX + nextMoveX),
					std::min(playerY, playerY + nextMoveY),
					playerW,
					playerH
				);

				if (tileBounds.intersectsRect(playerBounds))
				{
					log("Collision Detected!  Tile %i || x: %i, y: %i", gid, x, y);
					//collisionDetected = true;
				}
			}
		}
	}

	if (collisionDetected == false)
	{
		//player.updateObject(delta);
	}
}


void Level::update(float& delta, GameObject& player)
{
	// The current time
	// Since we will need to re-calculate the player's movement vector numerous times
	// during the update, we want to use a fixed time reference; if we always use the
	// current time, errors can be introduced due to the time elapsed while the
	// update is running

	// Flags to specify what kind of collision has occurred
	bool contactX = true, contactYbottom = true, contactYtop = true;

	// Reset collision statistics for this frame
	memset(&CollisionStats, 0, sizeof(CollisionData) * iterations);

	// Keep iterating the contact solver until the maximum number of iterations is reached
	// or no collisions are detected
	for (int iteration = 0; iteration < iterations && (contactX || contactYbottom || contactYtop); iteration++)
	{
		// Clear list of bounding boxes the player is within
		boundObjects.clear();

		// Calculate the amount of X and Y movement expected by the player this frame
		float nextMoveX = player.speedX * delta;
		float nextMoveY = player.speedY * delta;

		// Calculate the total bounding box of the player's current position
		// and his/her expected movement this frame

		// IMPORTANT! We must include the expected movement within the bounding box
		// so that we can correctly select which landscape objects to consider for
		// a potential collision
		// Get the player bounds relative to layer co-ordinates
		auto playerPos = worldObjects.at(0)->convertToNodeSpace(player.getPosition());
		auto playerSize = player.getContentSize();

		float playerX = playerPos.x;
		float playerY = playerPos.y;
		float playerW = playerSize.width;
		float playerH = playerSize.height;

		Rect playerBounds = Rect
		(
			std::min(playerX, playerX + nextMoveX),
			std::min(playerY, playerY + nextMoveY),
			playerW,
			playerH
		);

		// Check each object to see whether it intersects with the player's bounding box
		for (int o = 0; o < worldObjectCount; o++)
		{
			// We don't need to check all four corners on each object and player by hand
			// Using a neat quirk of mathematics, we can take the combined bounding box
			// of the player and the object. If it's width or height exceeds the total
			// width or height of the object + the player, then the bounding boxes do
			// not intersect, otherwise they do.
			

			// If a bounding box intersects with the player's bounding box, add the
			// geometry to the list of geometries to check for collisions
			if (playerBounds.intersectsRect(worldObjectBoundingBoxes[o]))
			{
				boundObjects.insert(o);
				CollisionStats[iteration].boundConstraints++;
			}
		}

		// No collisions found yet
		contactX = contactYbottom = contactYtop = false;

		float projectedMoveX, projectedMoveY, originalMoveX, originalMoveY;
		float vectorLength;
		int segments;

		// Store the original final expected movement of the player so we can
		// see if it has been modified due to a collision or potential collision later
		originalMoveX = nextMoveX;
		originalMoveY = nextMoveY;

		// Iterate over each object whose bounding box intersects with the player's bounding box
		// until a collision is found
		for (auto it = boundObjects.begin(); it != boundObjects.end() && !contactX && !contactYbottom && !contactYtop; it++)
		{
			// ================================================================================
			// Speculative contacts section
			//
			// We will traverse along the movement vector of the player from his/her current
			// position until the final position for the frame to check if any geometry lies
			// in the way. If so, the vector is adjusted to end at the geometry's intersection
			// with the player's movement vector. This solves the so-called 'bullet through
			// paper' problem.
			// ================================================================================

			//auto specAABB = playerBounds;
			//float top = worldObjectBoundingBoxes.at(*it).origin.y + worldObjectBoundingBoxes.at(*it).size.height;
			//float left =

			Rect tileBounds = worldObjectBoundingBoxes.at(*it);
			
			float thisLeftX = tileBounds.origin.x;
			float thisRightX = tileBounds.origin.x + tileBounds.size.width;
			float thisTopY = tileBounds.origin.y + tileBounds.size.height;
			float thisBottomY = tileBounds.origin.y;

			float otherLeftX = playerBounds.origin.x;
			float otherRightX = playerBounds.origin.x + playerBounds.size.width;
			float otherTopY = playerBounds.origin.y + playerBounds.size.height;
			float otherBottomY = playerBounds.origin.y;

			Rect specIntBounds = Rect(otherLeftX, otherBottomY, thisRightX - otherLeftX, thisTopY - otherBottomY);

			//auto specIntBounds = worldObjectBoundingBoxes.at(*it).unionWithRect(playerBounds);//.unionWithRect(specAABB);

			float unionX = specIntBounds.getMaxX() - specIntBounds.getMinX();
			float unionY = specIntBounds.getMaxY() - specIntBounds.getMinY();
			
			if (unionX >= 1 && unionY >= 1)
			{
				// We will test the four possible directions of player movement individually
				// dir: 0 = top, 1 = bottom, 2 = left, 3 = right
				for (int dir = 0; dir < 4; dir++)
				{
					// Skip the test if the expected direction of movement makes the test irrelevant
					// For example, we only want to test the top of the player's head when movement is
					// upwards, not downwards. This is really important! If we don't do this, we can
					// get stuck in a ceiling when falling for example.

					if (dir == 0 && nextMoveY > 0) continue;
					if (dir == 1 && nextMoveY < 0) continue;
					if (dir == 2 && nextMoveX > 0) continue;
					if (dir == 3 && nextMoveX < 0) continue;

					float minX = specIntBounds.getMinX();
					float maxX = specIntBounds.getMaxX();

					float minY = specIntBounds.getMinY();
					float maxY = specIntBounds.getMaxY();

					float safeMoveX = std::max(minX - playerX, playerX + playerW - maxX);
					float safeMoveY = std::max(maxY - playerY, playerY - minY);
					
					float safeVecLen = sqrt(safeMoveX * safeMoveX + safeMoveY * safeMoveY);

					// Calculate the length of the movement vector using Pythagoras
					vectorLength = sqrt(nextMoveX * nextMoveX + nextMoveY * nextMoveY);

					// Our current position along the anticipated movement vector of the player this frame
					projectedMoveX = nextMoveX * (safeVecLen / vectorLength);
					projectedMoveY = nextMoveY * (safeVecLen / vectorLength);

					vectorLength -= safeVecLen;

					segments = 0;

					// Advance along the vector until it intersects with some geometry
					// or we reach the end
					Vec2 upper = Vec2
					(
						player.collisionPoint[dir * 2].x + playerX + projectedMoveX,
						player.collisionPoint[dir * 2].y + playerY + projectedMoveY
					);

					Vec2 lower = Vec2
					(
						player.collisionPoint[dir * 2 + 1].x + playerX + projectedMoveX,
						player.collisionPoint[dir * 2 + 1].y + playerY + projectedMoveY
					);

					Rect bounds = worldObjectBoundingBoxes.at(*it);

					while (!bounds.containsPoint(upper) && !bounds.containsPoint(lower) && segments < vectorLength)
					{
						projectedMoveX += nextMoveX / vectorLength;
						projectedMoveY += nextMoveY / vectorLength;
						segments++;

						CollisionStats[iteration].specSteps++;
					}

					// If an intersection occurred...
					if (segments < vectorLength)
					{
						// Apply correction for over-movement
						if (segments > 0)
						{
							projectedMoveX -= nextMoveX / vectorLength;
							projectedMoveY -= nextMoveY / vectorLength;
						}

						// Adjust the X or Y component of the vector depending on
						// which direction we are currently testing
						if (dir >= 2 && dir <= 3) nextMoveX = projectedMoveX;
						if (dir >= 0 && dir <= 1) nextMoveY = projectedMoveY;
					}
				}
			}
			else
			{
				CollisionStats[iteration].specDiscards++;
			}

			// ================================================================================
			// Penetration resolution
			//
			// Here we look for existing collisions and nudge the player in the opposite
			// direction until the collision is solved. The purpose of iteration is because
			// the correction may cause collisions with other pieces of geometry. Iteration
			// also solves the so-called 'jitter' problem where a collision between the
			// player and the geometry is constantly solved and then re-introduced as the
			// player's position is nudged backwards and forwards between the same two points
			// repeatedly, creating jitter in the player's movement.
			// ================================================================================

			Rect playerNextBounds = Rect
			(
				playerX + nextMoveX, 
				playerY + nextMoveY,
				playerW + nextMoveX, 
				playerH + nextMoveY 
			);

			
			tileBounds = worldObjectBoundingBoxes.at(*it);

			thisLeftX = tileBounds.origin.x;
			thisRightX = tileBounds.origin.x + tileBounds.size.width;
			thisTopY = tileBounds.origin.y + tileBounds.size.height;
			thisBottomY = tileBounds.origin.y;

			otherLeftX = playerNextBounds.origin.x;
			otherRightX = playerNextBounds.origin.x + playerBounds.size.width;
			otherTopY = playerNextBounds.origin.y + playerBounds.size.height;
			otherBottomY = playerNextBounds.origin.y;

			//Rect specIntBounds = Rect(otherLeftX, otherBottomY, thisRightX - otherLeftX, thisTopY - otherBottomY);
			Rect intersectedBounds = tileBounds.unionWithRect(playerNextBounds);//Rect(otherLeftX, otherBottomY, thisRightX - otherLeftX, thisTopY - otherBottomY);//worldObjectBoundingBoxes.at(*it).unionWithRect(playerNextBounds);

			// Convert to int to prevent juddering of the character due to floating point rounding errors
			int intX = static_cast<int>(intersectedBounds.getMaxX() - intersectedBounds.getMinX());
			int intY = static_cast<int>(intersectedBounds.getMinY() - intersectedBounds.getMaxY());

			// We will test the four possible directions of player movement individually
			// dir: 0 = top, 1 = bottom, 2 = left, 3 = right
			for (int dir = 0; dir < 4; dir++)
			{
				Vec2 upper = Vec2
				(
					player.collisionPoint[dir * 2].x + playerX + nextMoveX,
					player.collisionPoint[dir * 2].y + playerY + nextMoveY
				);

				Vec2 lower = Vec2
				(
					player.collisionPoint[dir * 2 + 1].x + playerX + nextMoveX,
					player.collisionPoint[dir * 2 + 1].y + playerY + nextMoveY
				);

				if (intersectedBounds.containsPoint(upper) || intersectedBounds.containsPoint(lower))
				{
					switch (dir) 
					{
						case 0: nextMoveY += intY; break;
						case 1: nextMoveY -= intY; break;
						case 2: nextMoveX += intX; break;
						case 3: nextMoveX -= intX; break;
					}

					CollisionStats[iteration].penetrationCorrections++;
				}
			}

			// Detect what type of contact has occurred based on a comparison of
			// the original expected movement vector and the new one
			if (nextMoveY > originalMoveY && originalMoveY < 0)
			{
				contactYtop = true;
			}

			if (nextMoveY < originalMoveY && originalMoveY > 0)
			{
				contactYbottom = true;
			}

			if (abs(nextMoveX - originalMoveX) > 0.01f)
			{
				contactX = true;
			}

			// The player can't continue jumping if we hit the side of something, must fall instead
			// Without this, a player hiting a wall during a jump will continue trying to travel
			// upwards
			if (contactX && player.speedY < 0)
				player.speedY = nextMoveY = 0;

			if (contactX || contactYtop || contactYbottom)
			{
				CollisionStats[iteration].contacts++;
			}
		}

		// If a contact has been detected, apply the re-calculated movement vector
		// and disable any further movement this frame (in either X or Y as appropriate)
		if (contactYbottom || contactYtop)
		{
			playerY += nextMoveY;
			player.speedY = 0;

			if (contactYbottom)
				player.jumping = false;
		}

		if (contactX)
		{
			playerX += nextMoveX;
			player.speedX = 0;
		}
	}
}