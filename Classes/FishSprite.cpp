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
    
    PhysicsBody *body = PhysicsBody::createBox(getContentSize());
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
    setRotation( getRotation() + (angle - _prevAngle));
    _target = target;
    _prevAngle = angle;
}

void FishSprite::setFire(bool fire){
    unscheduleAllCallbacks();
    shouldFire = fire;
    if(shouldFire){
        schedule(schedule_selector(FishSprite::tick), 0.2f);
        tick(0);
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
    
    PhysicsBody *body = PhysicsBody::createBox(bubble->getContentSize());
    body->setGravityEnable(false);
    body->setRotationEnable(true);
    body->setCategoryBitmask(BUBBLE);
    body->setCollisionBitmask(ENEMY);
    body->setContactTestBitmask(ENEMY);
    bubble->setPhysicsBody(body);

    Vec2 impulseVec = target - getPosition();
    body->applyImpulse( impulseVec * (1000 - impulseVec.length()));
    
    runAction(Sequence::create(CallFunc::create([this]() { this->setTexture( "fishBubble.png"); }),
                               DelayTime::create(0.7f),
                               CallFunc::create([this]() { this->setTexture("fish.png"); }),
                               NULL ));
    return bubble;    
}

