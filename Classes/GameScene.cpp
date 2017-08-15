#include "GameScene.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d;

Scene* GameScene::createScene() {
    return GameScene::create();
}

bool GameScene::init()
{
    if ( !Scene::init() ) {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();

    auto background = Sprite::create("background.png");
    background->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height *0.5f));
    background->setScale(MAX(visibleSize.width / background->getContentSize().width,
                         visibleSize.height / background->getContentSize().height));
    this->addChild(background);

    return true;
}