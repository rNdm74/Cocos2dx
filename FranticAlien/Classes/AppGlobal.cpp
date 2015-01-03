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

float AppGlobal::getRandom(float begin, float end)
{
    double value;
    
    value = (double)rand() / RAND_MAX;
    value = value * (end - begin) + begin;
    
    return value;
}