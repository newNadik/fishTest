#include "MenuScene.h"
#include "ui/CocosGUI.h"
#include "GameScene.h"

USING_NS_CC;
using namespace cocos2d;
using namespace cocos2d::ui;

Scene* MenuScene::createScene() {
    return MenuScene::create();
}

bool MenuScene::init()
{
    if ( !Scene::init() ) {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();

    auto background = Sprite::create("menuBackground.png");
    background->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height *0.5f));
    background->setScale(visibleSize.width / background->getContentSize().width,
    visibleSize.height / background->getContentSize().height);
    this->addChild(background);

    auto button = Button::create();
    button->setTitleLabel(Label::createWithTTF("Play", "fonts/Marker Felt.ttf", 50));
    button->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.5f));
    button->loadTextures("buttonRed.png", "buttonRedPressed.png");
    button->setScale9Enabled(true);
    button->setSize(Size(button->getContentSize().width*22.0f, button->getContentSize().height*12.0f));

    button->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
        switch (type) {
            case ui::Widget::TouchEventType::ENDED:
                Director::getInstance()->replaceScene(GameScene::createScene());
                break;
            default:
                break;
        }
    });
    button->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.5f));

    this->addChild(button);
    return true;
}


void MenuScene::closeApp()
{
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
