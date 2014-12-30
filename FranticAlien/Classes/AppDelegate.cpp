#include "AppDelegate.h"
#include "AppGlobal.h"
#include "AppResources.h"
#include "SplashScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    
    //Texture2D::PVRImagesHavePremultipliedAlpha(true);
    
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    
    if(!glview) {
		glview = GLView::create("Frantic Alien");
		//glview = GLView::createWithRect("Frantic Alien", Rect(0,0, 800,600), 1.0f);
        //glview = GLView::createWithFullScreen("Frantic Alien");

        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    // create global area for game
    auto appGlobal = AppGlobal::getInstance();
    appGlobal->IsGameSceneRunning = false;
    
    // create gloat resources manager
    auto appResources = AppResources::getInstance();
    appResources->Load();
    
    // set design resolution for game
    glview->setDesignResolutionSize(1024, 768, ResolutionPolicy::NO_BORDER);
    
    // create a scene. it's an autorelease object
    auto scene = SplashScene::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
