#include "MenuComponent.h"
#include "GameObject.h"

USING_NS_CC;

PlayerMenuComponent* PlayerMenuComponent::create()
{
    auto ret = new PlayerMenuComponent();
    
    if (ret && ret->init())
    {
        ret->autorelease();
        ret->setTag(MENU);
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool PlayerMenuComponent::init()
{
    int _ptr = 0;
    
    for(auto s : ITEMS)
    {
        auto name = FILE_SUFFIX + s + FILE_PREFIX;
        
        auto menu_item = Sprite::create(name);
        menu_item->setTag(_ptr++);
        
        this->addChild(menu_item, -10);
    }
    
    return true;
}

bool PlayerMenuComponent::showMenu(GameObject &gameObject)
{
    // Show menu
    auto center = Vec2(getContentSize().width / 2, 20 + getContentSize().height / 2);
    
    // Get all children from menu node
    auto children = this->getChildren();
    
    // Displays the radial menu around sprite
    for (int i = 0; i < children.size(); i++)
    {
        float radians = -0.2 + (i * 50) * (PI / 180);
        
        float x = center.x + cos(radians) * 80;
        float y = center.y + sin(radians) * 80;
        
        children.at(i)->runAction(MoveTo::create(0.1f, Vec2(x, y)));
        children.at(i)->runAction(ScaleTo::create(0.1f, 0.8f));
    }
    
    return true;
}

bool PlayerMenuComponent::hideMenu(GameObject &gameObject)
{
    // Hides menu
    auto center = Vec2(getContentSize().width / 2, getContentSize().height / 2);
    
    auto children = this->getChildren();
    
    for(auto child : children)
    {
        child->runAction(MoveTo::create(0.1, center));
        child->runAction(ScaleTo::create(0.1f, 0.0f));
    }
    
    return true;
}