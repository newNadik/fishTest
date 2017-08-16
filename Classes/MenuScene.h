#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;
using namespace cocos2d::ui;

class MenuScene : public Scene
{
public:
    static Scene* createScene();

    virtual bool init();
    CREATE_FUNC(MenuScene);
    void closeApp();

};

#endif // __MENU_SCENE_H__
