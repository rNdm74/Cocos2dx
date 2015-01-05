#include "AppDelegate.h"
#include "AppGlobal.h"
#include "AppResources.h"
#include "SplashScene.h"

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
		//glview = GLView::createWithRect("Frantic Alien", Rect(0, 0, 480, 320));		
        //glview = GLView::createWithFullScreen("Frantic Alien");

		glfwSetInputMode(glview->getWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        director->setOpenGLView(glview);
		director->setAlphaBlending(true);
    }
	
    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0/60);

	// set design resolution for game
	glview->setDesignResolutionSize(960, 640, ResolutionPolicy::NO_BORDER);


		
	/*log("Scale factor     : %.0f", director->getContentScaleFactor());
	log("Screen size      : {%.0f, %.0f}", glview->getFrameSize().width, glview->getFrameSize().height);
	log("Tile size        : {%.0f, %.0f}", 70.0f, 70.0f);*/
    
	// create global resources manager
	auto appResources = AppResources::getInstance();
	appResources->initLoad();

    // create global area for game
    auto appGlobal = AppGlobal::getInstance();
    appGlobal->IsGameSceneRunning = false;
        		
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
