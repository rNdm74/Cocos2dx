#ifndef  _APP_GLOBAL_H_
#define  _APP_GLOBAL_H_

#include "cocos2d.h"

/**
@brief    The cocos2d Application.

The reason for implement as private inheritance is to hide some interface call by Director.
*/
class  AppGlobal
{
private:
    static AppGlobal* m_pInstance;
    
public:
    static AppGlobal* getInstance();
    
    bool IsGameSceneRunning;
    int ActiveLevel;
    cocos2d::Point StartPosition;
    
    std::string getActiveLevel(){
    
        char buffer[20];
        sprintf (buffer, "%d", ActiveLevel);
        
        return buffer;
    };
    
private:
    AppGlobal();
    virtual ~AppGlobal();
};

#endif // _APP_GLOBAL_H_

