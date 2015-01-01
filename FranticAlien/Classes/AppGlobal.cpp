#include "AppGlobal.h"

USING_NS_CC;

AppGlobal* AppGlobal::m_pInstance = NULL;

AppGlobal* AppGlobal::getInstance()
{
    return m_pInstance ? m_pInstance : m_pInstance = new AppGlobal();
}

AppGlobal::AppGlobal() {
    ActiveLevel = 1;
	//SetupScaleFactors();
}

AppGlobal::~AppGlobal()
{
}

float AppGlobal::GetScaleX()
{
	return _scaleX;
}

float AppGlobal::GetScaleY()
{
	return _scaleY;
}

float AppGlobal::GetScaleFactor()
{ 
	return _scaleFactor;
}

Vec2 AppGlobal::ScalePoint(Vec2 point)
{
	Size designSize = { 480, 320 };

	Size winSize = Director::getInstance()->getWinSize();

	Size scaleFactor = Size(winSize.width / designSize.width, winSize.height / designSize.height);

	return Vec2(point.x * scaleFactor.width, point.y * scaleFactor.height);
}

