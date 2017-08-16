//
//  FishSprite.hpp
//  FishTest
//
//  Created by Pro on 8/16/17.
//
//

#ifndef FishSprite_hpp
#define FishSprite_hpp

#include "cocos2d.h"
#include <stdio.h>
using namespace cocos2d;
using namespace std;

class FishSprite : public Sprite
{
    float _prevAngle = 0.0f;
    bool shouldFire = false;
    Vec2 _target;
    const float _oneTickAngle = 5.0f;
    bool isRotating = false;
    float _currentAngle = 0.0f;
    Vec2 convertAngleToVec(float angle);
public:
    static FishSprite* createSprite();
    virtual bool init();
    void tick(float dt);
    void rotateTick(float dt);

    CREATE_FUNC(FishSprite);
    
    void setFire(bool fire);
    void rotateTo( Vec2 target );
    Sprite *makeBubble( Vec2 target );
};

#endif /* FishSprite_hpp */
