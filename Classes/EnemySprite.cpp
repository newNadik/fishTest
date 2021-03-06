//
//  EnemySprite.cpp
//  FishTest
//
//  Created by Pro on 8/16/17.
//
//

#include "EnemySprite.hpp"
#include "Constants.h"
EnemySprite* EnemySprite::createSprite() {
    return EnemySprite::create();
}

bool EnemySprite::init()
{
    if ( !Sprite::init() ) {
        return false;
    }
    setTexture("badFish.png");
    setScale(0.35f);
    
    PhysicsBody *body = PhysicsBody::createCircle(getContentSize().width*0.35f);
    body->setGravityEnable(false);
    body->setDynamic(true);
    body->setRotationEnable(true);
    body->setCategoryBitmask(ENEMY);
    body->setCollisionBitmask(HERO);
    body->setContactTestBitmask(HERO|BUBBLE);
    setPhysicsBody(body);
    
    return true;
}
void EnemySprite::moveTo(Vec2 target){    

    setRotation( -CC_RADIANS_TO_DEGREES((getPosition() - target).getAngle())+90);

    getPhysicsBody()->applyImpulse((target - getPosition())*400);
    
    RotateBy *rotate1 = RotateBy::create(1.0f, 5);
    RotateBy *rotate2 = RotateBy::create(1.0f, -5);
    Sequence *seq = Sequence::create(rotate1->clone(), rotate1->reverse(),
                                     rotate2->clone(), rotate2->reverse(), NULL);
    Repeat *action = Repeat::create(seq, -1);
    runAction(action);
}


