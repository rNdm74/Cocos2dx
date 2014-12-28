#include "TileMapTile.h"
#include "AppResources.h"
#include "AppGlobal.h"

USING_NS_CC;

TileMapTile::TileMapTile()
{
   
}

TileMapTile* TileMapTile::create(float x, float y, int gid)
{
    
	std::string spriteFrameName = AppResources::getInstance()->getFrameName(gid);
    
    //log("%s", spriteFrameName.c_str());
    if(gid == 126)
    {
        AppGlobal::getInstance()->StartPosition = Point(x, y);
    }
    
	TileMapTile* sprite = new TileMapTile();
    
	if(sprite && sprite->initWithSpriteFrameName(spriteFrameName))
	{
        sprite->setTag(gid);
        
		sprite->autorelease();

		sprite->setPosition(x, y);
        
        if(gid == 89 || gid == 90)
        {
            sprite->setShadow(Vec2(-1, -2));
        }
        else if(gid == 74)
        {
        }
        
		return sprite;
	}

	CC_SAFE_DELETE(sprite);

	return NULL;
}

void TileMapTile::setShadow(Vec2 offset)
{
    _lightPosition = Vec2(Director::getInstance()->getVisibleSize().width, Director::getInstance()->getVisibleSize().height);
    
    // Step 1
    _shadow = Sprite::create();
    
    _shadow->setSpriteFrame(this->getSpriteFrame());
    
    // Step 2
    _shadow->setAnchorPoint(Point(0,0)); // position it to the center of the target node
    _shadow->setPosition(offset);
    
    // Step 3
    _shadow->setRotation(this->cocos2d::Sprite::getRotation());
    _shadow->setScale(this->cocos2d::Sprite::getScale());
    
    // Step 4
    //_shadow->setScaleY(_lightPosition.y / 425);
    _shadow->setContentSize(Size(this->getContentSize().width - 2, this->getContentSize().height));
    _shadow->setScaleX(1.0f);
    _shadow->setScaleY(1.0f);
    // Step 5
    //shadow->runAction(FlipY::create(true));
    
    // Step 6
    //_shadow->setSkewX(calculateSkew());
    
    // Step 6
    _shadow->setColor(Color3B(0, 0, 0));
    _shadow->setOpacity(50);
    
    // Step 7
    //shadow->setTag(SHADOW_TAG);
    
    this->addChild(_shadow, -10);
}

float TileMapTile::calculateSkew()
{
    //Node* parent = node->getParent();
    
    float ED = _lightPosition.y - this->getPosition().y;
    float EL = _lightPosition.x - (this->getPosition().x + _shadow->getPosition().x);
    float DLE = atan(ED / EL);
    float DB = _shadow->getContentSize().height * _shadow->getScaleY() + this->getContentSize().height * this->getScaleY();
    float CB = tan(PI / 2 - DLE) * DB;
    float AB = _shadow->getContentSize().height * _shadow->getScaleY();
    float skew = 90.0 - toDegrees(atan(AB / CB));
    
    return skew;
}