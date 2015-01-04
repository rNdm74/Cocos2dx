#include "MenuComponent.h"
#include "GameObject.h"

MenuComponentItem* MenuComponentItem::createMenuWithFrameName(std::string frameName)
{
	auto sprite = new MenuComponentItem();

	if (sprite && sprite->initWithFile(frameName))
	{
		sprite->autorelease();
		sprite->setName(frameName);
		sprite->initListeners();

		return sprite;
	}

	CC_SAFE_DELETE(sprite);

	return NULL;
}

void MenuComponentItem::initListeners()
{
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = [=](Touch* touch, Event* event) -> bool {

		auto touchEvent = static_cast<EventTouch*>(event);

		auto node = touchEvent->getCurrentTarget();
				
		auto tPos = node->getParent()->convertTouchToNodeSpace(touch);
		auto nBox = node->getBoundingBox();

		if (nBox.containsPoint(tPos))
		{
			log(node->getName().c_str());

			auto scaleUpAction = ScaleTo::create(0.1, 1.0);
			auto scaleDownAction = ScaleTo::create(0.1, 0.8);

			// Button effect
			node->runAction(Sequence::createWithTwoActions(scaleUpAction, scaleDownAction));
		}

		return true;
	};


	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

bool PlayerMenuComponent::addMenu(GameObject &gameObject)
{
    int _ptr = 0;
    
	auto spriteColors = { "Beige", "Blue", "Green", "Pink", "Yellow" };

	for (auto color : spriteColors)
    {
		std::string name( color );

		auto menu_item = MenuComponentItem::createMenuWithFrameName(FILE_PREFIX + name + FILE_SUFFIX);
		menu_item->setName(FILE_PREFIX + name + FILE_SUFFIX);
        menu_item->setTag(_ptr++);
        
        gameObject.addChild(menu_item, -10);
    }
    
	return true;
}

void PlayerMenuComponent::showMenu(GameObject &gameObject)
{
    // Show menu
	auto center = Vec2(gameObject.getContentSize().width / 2, 20 + gameObject.getContentSize().height / 2);
    
    // Get all children from gameObject
    auto children = gameObject.getChildren();
    
    // Displays the radial menu around sprite
    for (int i = 0; i < children.size(); i++)
    {
		// Work out angle
        float radians = -0.2 + (i * 50) * (PI / 180);
        
		// x,y co-ordinate
        float x = center.x + cos(radians) * 80;
        float y = center.y + sin(radians) * 80;
        
        children.at(i)->runAction(MoveTo::create(0.1f, Vec2(x, y)));
        children.at(i)->runAction(ScaleTo::create(0.1f, 0.8f));
    }
    
	this->_isActive = true;
}

void PlayerMenuComponent::hideMenu(GameObject &gameObject)
{
    // Hides menu
	auto center = Vec2(gameObject.getContentSize().width / 2, gameObject.getContentSize().height / 2);
    
	for (auto child : gameObject.getChildren())
    {
        child->runAction(MoveTo::create(0.1, center));
        child->runAction(ScaleTo::create(0.1f, 0.0f));
    }
    
	this->_isActive = false;
}