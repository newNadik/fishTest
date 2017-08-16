//
//  GameScene.hpp
//  FishTest
//
//  Created by Pro on 8/16/17.
//
//

#ifndef GameScene_hpp
#define GameScene_hpp


#include "cocos2d.h"
#include "FishSprite.hpp"
#include "EnemySprite.hpp"

using namespace cocos2d;
using namespace cocos2d::ui;

class GameScene : public Layer
{
    FishSprite *heroFish;
    
    Size winSize;
    
    void initListeners();
    void initUI();
    void initEnemies(int count);
    void goMenu();
    
    int getRandom(int min, int max);
    float getRandom(float min, float max);
    
    virtual bool onTouchBegan(Touch*, Event*);
    virtual void onTouchEnded(Touch*, Event*);
    virtual void onTouchMoved(Touch*, Event*);
    virtual void onTouchCancelled(Touch*, Event*);
    bool onContactBegin( PhysicsContact &contact );

public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    CREATE_FUNC(GameScene);
    
};

#endif
