#include "AppGlobal.h"

AppGlobal* AppGlobal::m_pInstance = NULL;

AppGlobal* AppGlobal::getInstance()
{
    return m_pInstance ? m_pInstance : m_pInstance = new AppGlobal();
}

AppGlobal::AppGlobal() {
    ActiveLevel = 1;
}

AppGlobal::~AppGlobal()
{
}

void AppGlobal::initMouseListener()
{	
	auto mouseListener = EventListenerMouse::create();

	mouseListener->onMouseMove = [=](Event* event){

		// Cast Event to EventMouse for position details like above
		auto eventMouse = static_cast<EventMouse*>(event);

		this->cursorMove = Vec2(eventMouse->getCursorX(), eventMouse->getCursorY());

		if (Director::getInstance()->getRunningScene()->isRunning())
		{
			auto layer = Director::getInstance()->getRunningScene()->getChildByTag(KTagSceneLayer);

			auto cursor = layer->getChildByTag(kTagCursor);

			cursor->setPosition(cursorMove);
		}		
	};

	mouseListener->onMouseDown = [=](Event* event){

		auto layer = Director::getInstance()->getRunningScene()->getChildByTag(KTagSceneLayer);

		auto cursor = static_cast<Sprite*>(layer->getChildByTag(kTagCursor));

		cursor->setSpriteFrame("tapTick.png");

		this->mouseUp = false;
		this->mouseDown = true;
	};

	mouseListener->onMouseUp = [=](Event* event){

		auto layer = Director::getInstance()->getRunningScene()->getChildByTag(KTagSceneLayer);

		auto cursor = static_cast<Sprite*>(layer->getChildByTag(kTagCursor));

		cursor->setSpriteFrame("tap.png");

		this->mouseUp = true;
		this->mouseDown = false;
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(mouseListener, 1);
}

void AppGlobal::addCursor(Layer& layer)
{
	auto _cursor = Sprite::createWithSpriteFrameName("tap.png");
	_cursor->setTag(kTagCursor);
	_cursor->setAnchorPoint(Vec2(0.5, 0.5));
	_cursor->setPosition(cursorMove);

	layer.addChild(_cursor, kTagCursor);
}

float AppGlobal::getRandom(float begin, float end)
{
    double value;
    
    value = (double)rand() / RAND_MAX;
    value = value * (end - begin) + begin;
    
    return value;
}