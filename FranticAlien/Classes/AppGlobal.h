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

	float _scaleX;
	float _scaleY;
	float _scaleFactor;

public:
    static AppGlobal* getInstance();
    
    bool IsGameSceneRunning;
    int ActiveLevel;
    cocos2d::Point StartPosition;

	float GetRandom(float begin, float end)
	{
		double value;

		value = (double)rand() / RAND_MAX;
		value = value * (end - begin) + begin;

		return value;
	};
    
    std::string GetActiveLevel() { return std::to_string(ActiveLevel); };

	float GetScaleX();
	float GetScaleY();
	float GetScaleFactor();

	cocos2d::Vec2 ScalePoint(cocos2d::Vec2 point);
	    
private:
    AppGlobal();
    virtual ~AppGlobal();	
};

#define RAND(begin, end)  ( AppGlobal::getInstance()->GetRandom( (begin), (end) ) )

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

