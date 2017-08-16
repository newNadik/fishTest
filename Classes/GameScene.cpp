//
//  GameScene.cpp
//  FishTest
//
//  Created by Pro on 8/16/17.
//
//

#include "GameScene.hpp"
#include "ui/CocosGUI.h"
#include "MenuScene.h"
#include "Constants.h"
USING_NS_CC;


Scene* GameScene::createScene() {    
    auto layer = new GameScene;
    if (layer)
    {
        auto scene = Scene::createWithPhysics();
        scene->addChild(layer);
        if (layer->init()) return scene;
    }
    return nullptr;
}

bool GameScene::init()
{
    winSize = Director::getInstance()->getWinSize();
    
    initListeners();
    initUI();
    
    heroFish = FishSprite::createSprite();
    heroFish->setPosition(Vec2(winSize.width * 0.5f, winSize.height *0.5f));
    this->addChild(heroFish);
    
    initEnemies(getRandom(3, 10));
    
    return true;
}
void GameScene::initEnemies(int count){
    
    for (int i=0; i<count; i++) {
        EnemySprite *enemy = EnemySprite::createSprite();
        
        float posX = getRandom(1,5)==1?getRandom(-0.1f, 0.3f):getRandom(0.7f, 1.1f);
        float posY = getRandom(1,5)==1?getRandom(-0.1f, 0.3f):getRandom(0.7f, 1.1f);
        
        enemy->setPosition(Vec2(winSize.width * posX, winSize.height *posY));
        enemy->moveTo(Vec2(winSize.width * 0.5f, winSize.height *0.5f));
        this->addChild(enemy);
    }
}
void GameScene::initListeners(){
    auto touchListener = EventListenerTouchOneByOne::create();    
    touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}
bool GameScene::onTouchBegan(Touch* touch, Event* event)
{
    heroFish->rotateTo(touch->getLocation());
    heroFish->setFire(true);
    return true;
}

void GameScene::onTouchEnded(Touch* touch, Event* event) {
    heroFish->setFire(false);
}
void GameScene::onTouchMoved(Touch* touch, Event* event) {
    heroFish->rotateTo(touch->getLocation());
}
void GameScene::onTouchCancelled(Touch* touch, Event* event) {
    heroFish->setFire(false);
}

bool GameScene::onContactBegin(cocos2d::PhysicsContact &contact)
{
    PhysicsBody *a = contact.getShapeA()->getBody();
    PhysicsBody *b = contact.getShapeB()->getBody();

    if ( ( ENEMY == a->getCategoryBitmask() && BUBBLE == b->getCategoryBitmask() ) ||
        ( BUBBLE == a->getCategoryBitmask() && ENEMY == b->getCategoryBitmask() ) ) {
        if(a->getNode() !=nullptr) a->getNode()->removeFromParentAndCleanup(true);
        if(b->getNode() !=nullptr) b->getNode()->removeFromParentAndCleanup(true);

        initEnemies(2);
    }
    else if( ( ENEMY == a->getCategoryBitmask() && HERO == b->getCategoryBitmask() ) ||
            ( HERO == a->getCategoryBitmask() && ENEMY == b->getCategoryBitmask() ) ) {
        goMenu();
    }
    return true;
}

void GameScene::initUI(){
    auto background = Sprite::create("background.png");
    background->setPosition(Vec2(winSize.width * 0.5f, winSize.height *0.5f));
    background->setScale(MAX(winSize.width / background->getContentSize().width,
                             winSize.height / background->getContentSize().height));
    this->addChild(background);
    
    ParticleSystemQuad *bulbParticle = ParticleSystemQuad::create("particle_texture.plist");
    bulbParticle->setPosition(Vec2(winSize.width / 2, 0));
    this->addChild(bulbParticle);
    
    auto menuButton = Button::create();
    menuButton->setTitleLabel(Label::createWithTTF("Menu", "fonts/Marker Felt.ttf", 30));
    menuButton->setPosition(Vec2(menuButton->getTitleRenderer()->getContentSize().width * 0.6f,
                                 winSize.height - menuButton->getTitleRenderer()->getContentSize().height * 1.4f));
    menuButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
        switch (type) {
            case Widget::TouchEventType::ENDED: goMenu(); break;
            default: break;
        }
    });
    this->addChild(menuButton, 10);
}

void GameScene::goMenu(){
    Director::getInstance()->replaceScene(TransitionCrossFade::create(0.1f, MenuScene::createScene()));
}

int GameScene::getRandom(int min, int max) { return min + rand() % max; }
float GameScene::getRandom(float min, float max) {
    return min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max-min)));
}
