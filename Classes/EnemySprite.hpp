//
//  EnemySprite.hpp
//  FishTest
//
//  Created by Pro on 8/16/17.
//
//

#ifndef EnemySprite_hpp
#define EnemySprite_hpp

#include "cocos2d.h"
#include <stdio.h>
using namespace cocos2d;
using namespace std;

class EnemySprite : public Sprite
{
public:
    static EnemySprite* createSprite();
    virtual bool init();
    CREATE_FUNC(EnemySprite);
    void moveTo(Vec2 target);
    
};

#endif /* FishSprite_hpp */
