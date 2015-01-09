#ifndef __FranticAlien__CONSTANTS_H__
#define __FranticAlien__CONSTANTS_H__

#include <string>

// PNG assets
#define BACKGROUND_PNG		"background.png"
#define CHARACTERS_PNG		"characters.png"
#define CONTROLS_PNG		"controls.png"
#define HUD_PNG				"hud.png"
#define ITEMS_PNG			"items.png"
#define PARTICLES_PNG		"particles.png"
#define TILES_PNG			"tiles.png"

// PLIST assets
#define BACKGROUND_PLIST	"background.plist"
#define CHARACTERS_PLIST	"characters.plist"
#define CONTROLS_PLIST		"controls.plist"
#define HUD_PLIST			"hud.plist"
#define ITEMS_PLIST			"items.plist"
#define PARTICLES_PLIST		"particles.plist"
#define TILES_PLIST			"tiles.plist"

#define kTagCursor 999
#define KTagSceneLayer 1

#define kTagScrollingBackground 0
#define kTagScrollingCloud 1
#define kTagScrollingBush 2

#define kBackgroundLayer 1
#define kMidgroundLayer 2
#define kForegroundLayer 3
#define PTM_RATIO 32.0

#define FILE_PREFIX "alien"
#define FILE_SUFFIX "_badge2.png"

#define MENU 1

#define PI 3.14159265

const float kMinVelocityX						= 1.0f;
const float kMaxVelocityX						= 15.0f;
const float kStopVelocity						= 0.70f; // 98%

const float kGameObjectFixtureDensity			= 1.0f;
const float kGameObjectFixtureFriction			= 0.3f;
const float kGameObjectFixtureRestitution		= 0.1f;
const int	kGameObjectFixtureFilterMaskBits	= 0xffff;



const float kPixelsPerMeter						= 32.0f;
const float kGravity							= -9.8f; // adjust this to taste
const float kUpdateInterval						= 1.0f / 60.0f;
const double kSecondsPerUpdate					= 0.1;

const std::string kLevelTMX						= "level1.tmx";
const std::string kPlayerFileName				= "alienBeige.png";

//enumeration of possible input states
enum EState {
	STATE_STOP,
	STATE_LEFT,
	STATE_RIGHT,
	STATE_UP,
	STATE_DOWN,
	STATE_JUMP,
	STATE_ENTER,
	STATE_ESCAPE,
	STATE_HUD,
	STATE_SPRINT,
};

enum kFilterCatagory 
{
	BOUNDARY		= 0x0001,
	PLAYER			= 0x0002,
	LADDER			= 0x0004,
	ENEMY			= 0x0008,
	LADDER_SENSOR	= 0x0010,
	//FRIENDLY_TOWER = 0x0020,
	//RADAR_SENSOR = 0x0040,
};

enum
{
	kFilterCategoryLevel = 0x01,
	kFilterCategorySolidObject = 0x02,
	kFilterCategoryNonSolidObject = 0x04
};

enum
{
	kTagNode,
	kTagPlayer,
	kTagStartPosition
};

#endif /* defined(__CONSTANTS__) */
