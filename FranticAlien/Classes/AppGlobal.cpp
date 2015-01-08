#include "AppGlobal.h"
#include "Constants.h"

AppGlobal* AppGlobal::m_pInstance = NULL;

AppGlobal* AppGlobal::getInstance()
{
    return m_pInstance ? m_pInstance : m_pInstance = new AppGlobal();
}

AppGlobal::AppGlobal() {
    ActiveLevel = 1;

	state = STATE_STOP;
	previousState = state;
}

AppGlobal::~AppGlobal()
{
}

void AppGlobal::initMouseListener()
{	
	auto listener = EventListenerMouse::create();

	listener->onMouseMove = [=](Event* event)
	{
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

	listener->onMouseDown = [=](Event* event)
	{
		auto layer = Director::getInstance()->getRunningScene()->getChildByTag(KTagSceneLayer);

		auto cursor = static_cast<Sprite*>(layer->getChildByTag(kTagCursor));

		cursor->setSpriteFrame("tapTick.png");

		this->mouseUp = false;
		this->mouseDown = true;
	};

	listener->onMouseUp = [=](Event* event)
	{
		auto layer = Director::getInstance()->getRunningScene()->getChildByTag(KTagSceneLayer);

		auto cursor = static_cast<Sprite*>(layer->getChildByTag(kTagCursor));

		cursor->setSpriteFrame("tap.png");

		this->mouseUp = true;
		this->mouseDown = false;
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
}

void AppGlobal::initKeyboardListener()
{
	// Keyboard input
	auto listener = EventListenerKeyboard::create();

	listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event *event)
	{
		// track the previous pressed key
		previousState = state;

		switch (keyCode)
		{
			case EventKeyboard::KeyCode::KEY_SHIFT:
				state = STATE_SPRINT;
				break;
			case EventKeyboard::KeyCode::KEY_SPACE:
				state = STATE_HUD;
				break;
			case EventKeyboard::KeyCode::KEY_ESCAPE:
				state = STATE_ESCAPE;
				break;
			case EventKeyboard::KeyCode::KEY_TAB:
				state = STATE_HUD;
				break;
			case EventKeyboard::KeyCode::KEY_ENTER:
				state = STATE_ENTER;
				break;
			case EventKeyboard::KeyCode::KEY_KP_ENTER:
				state = STATE_ENTER;
				break;
			case EventKeyboard::KeyCode::KEY_RETURN:
				state = STATE_ENTER;
				break;
			case EventKeyboard::KeyCode::KEY_W:
				state = STATE_UP;
				break;
			case EventKeyboard::KeyCode::KEY_S:
				state = STATE_DOWN;
				break;
			case EventKeyboard::KeyCode::KEY_A:
				state = STATE_LEFT;
				break;
			case EventKeyboard::KeyCode::KEY_D:
				state = STATE_RIGHT;
				break;
			case EventKeyboard::KeyCode::KEY_UP_ARROW:
				state = STATE_UP;
				break;
			case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
				state = STATE_DOWN;
				break;
			case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
				state = STATE_LEFT;
				break;
			case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
				state = STATE_RIGHT;
				break;
		}
	};

	listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event *event)
	{
		state = STATE_STOP;
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
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