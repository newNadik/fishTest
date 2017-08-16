//
//  FishSprite.cpp
//  FishTest
//
//  Created by Pro on 8/16/17.
//
//

#include "FishSprite.hpp"
#include "Constants.h"
FishSprite* FishSprite::createSprite() {
    return FishSprite::create();
}

bool FishSprite::init()
{
    if ( !Sprite::init() ) {
        return false;
    }
    setTexture("fish.png");
    setScale(0.35f);
    
    PhysicsBody *body = PhysicsBody::createCircle(getContentSize().width*0.35f);
    body->setGravityEnable(false);
    body->setRotationEnable(true);
    body->setCategoryBitmask(HERO);
    body->setCollisionBitmask(ENEMY);
    body->setContactTestBitmask(HERO|ENEMY);
    setPhysicsBody(body);

    return true;
}

void FishSprite::rotateTo( Vec2 target ){
    
    getPhysicsBody()->setAngularVelocityLimit(5.0f);
    auto diff = getPosition() - target;
    auto angle = CC_RADIANS_TO_DEGREES(atan2(diff.x, diff.y));
    _target = target;
    _prevAngle = angle;
    if (!isRotating) {
        schedule(schedule_selector(FishSprite::rotateTick), 0.02f);
        isRotating = true;
    }
}

void FishSprite::setFire(bool fire){
    unschedule(schedule_selector(FishSprite::tick));
    shouldFire = fire;
    if(shouldFire){
        schedule(schedule_selector(FishSprite::tick), 0.25f);
    }
}
void FishSprite::rotateTick(float dt) {
    if (_currentAngle - _prevAngle > 3 * _oneTickAngle) {
        _currentAngle -= _oneTickAngle;
        setRotation(_currentAngle);
    } else if (_currentAngle - _prevAngle < -3 * _oneTickAngle){
        _currentAngle += _oneTickAngle;
        setRotation(_currentAngle);
    } else {
        unschedule(schedule_selector(FishSprite::rotateTick));
        isRotating = false;
        if( !isScheduled(schedule_selector(FishSprite::tick)) )
            getParent()->addChild(makeBubble(_target));
    }
}
void FishSprite::tick(float dt){
    if (shouldFire) {
        getParent()->addChild(makeBubble(_target));
    }
}

Sprite* FishSprite::makeBubble( Vec2 target ){
    Sprite *bubble = Sprite::create("bubble.png");
    bubble->setScale(0.35f);
    bubble->setPosition(Vec2(getPosition()));
    bubble->setOpacity(0.0f);
    bubble->runAction(FadeIn::create(0.5f));
    
    PhysicsBody *body = PhysicsBody::createCircle(bubble->getContentSize().width/2);
    body->setGravityEnable(false);
    body->setRotationEnable(true);
    body->setCategoryBitmask(BUBBLE);
    body->setCollisionBitmask(ENEMY);
    body->setContactTestBitmask(ENEMY);
    bubble->setPhysicsBody(body);

    auto winSize = Director::getInstance()->getWinSize();

    Vec2 impulseVec = target - getPosition();
    body->applyImpulse(convertAngleToVec(_currentAngle-180)*500);
    
    runAction(Sequence::create(CallFunc::create([this]() { this->setTexture( "fishBubble.png"); }),
                               DelayTime::create(0.7f),
                               CallFunc::create([this]() { this->setTexture("fish.png"); }),
                               NULL ));
    return bubble;    
}

Vec2 FishSprite::convertAngleToVec(float angle)
{
    float halfOfScreen = Director::getInstance()->getWinSize().width/2;
    Vec2 result;
    float radAngle = CC_DEGREES_TO_RADIANS(angle);
    result = Vec2(halfOfScreen * sinf(radAngle), halfOfScreen * cosf(radAngle));
    return result;
}
