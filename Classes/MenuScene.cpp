#include "MenuScene.h"
#include "ui/CocosGUI.h"
#include "GameScene.hpp"
USING_NS_CC;


Scene* MenuScene::createScene() {
    return MenuScene::create();
}

bool MenuScene::init()
{
    if ( !Scene::init() ) {
        return false;
    }
    auto winSize = Director::getInstance()->getWinSize();

    auto background = Sprite::create("menuBackground.png");
    background->setPosition(Vec2(winSize.width * 0.5f, winSize.height *0.5f));
    background->setScale(winSize.width / background->getContentSize().width,
                         winSize.height / background->getContentSize().height);
    this->addChild(background);

    auto button = Button::create();
    button->setTitleLabel(Label::createWithTTF("Play", "fonts/Marker Felt.ttf", 50));
    button->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f));
    button->loadTextures("buttonRed.png", "buttonRedPressed.png");
    button->setScale9Enabled(true);
    button->setContentSize(Size(button->getTitleRenderer()->getContentSize().width * 1.3f,
                                button->getTitleRenderer()->getContentSize().height * 1.3f ));

    button->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
        switch (type) {
            case Widget::TouchEventType::ENDED:
                Director::getInstance()->replaceScene(TransitionCrossFade::create(0.1f, GameScene::createScene()));
                break;
            default:
                break;
        }
    });

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
