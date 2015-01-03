#ifndef  __FranticAlien__APP_GLOBAL_H_
#define  __FranticAlien__APP_GLOBAL_H_

#include "cocos2d.h"

enum EDirection{
    DIR_LEFT,
    DIR_RIGHT,
    DIR_UP,
    DIR_DOWN
};

class  AppGlobal
{
public:
    bool IsGameSceneRunning;
    int ActiveLevel;
    cocos2d::Point StartPosition;
    
public:
    static AppGlobal* getInstance();
    
	float getRandom(float begin, float end);
    
    std::string GetActiveLevel() { return std::to_string(ActiveLevel); };
	
    inline EDirection getDirection() { return _direction; }
    inline void setDirection(EDirection direction) { _direction = direction; }
    
private:
    AppGlobal();
    virtual ~AppGlobal();
    
    static AppGlobal* m_pInstance;
    
    EDirection _direction;
};

#define RAND(begin, end)  ( AppGlobal::getInstance()->getRandom( (begin), (end) ) )

//#define GETSCALEX ( AppGlobal::getInstance()->GetScaleX() )
//#define GETSCALEY ( AppGlobal::getInstance()->GetScaleY() )
//#define GETSCALEFACTOR ( AppGlobal::getInstance()->GetScaleFactor() )
//
//#define SCALEX(p) ( (p) * GETSCALEX )
//#define SCALEY(p) ( (p) * GETSCALEY )
//#define SCALEPOSITION(x,y) ( Vec2( GETSCALEX * (x) * GETSCALEFACTOR, GETSCALEY * (y) * GETSCALEFACTOR ) )
//#define SCALEFONT(p) ( (p) * SCALEY * GETSCALEFACTOR )
//
//#define SCALENODE_XY(n) n->setScaleX(GETSCALEX); n->setScaleY(GETSCALEY)
//
//#define SCALENODE_Y(n) n->setScale(GETSCALEY)


#endif // _APP_GLOBAL_H_

