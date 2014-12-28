#include "AppGlobal.h"

USING_NS_CC;

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
