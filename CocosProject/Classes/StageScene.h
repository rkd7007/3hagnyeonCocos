#ifndef __STAGE_SCENE_H__
#define __STAGE_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif


class StageScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	void PlayStage1(Ref* sender);
	void PlayStage2(Ref* sender);
	void PlayStage3(Ref* sender);

    // implement the "static create()" method manually
    CREATE_FUNC(StageScene);
};

#endif // __HELLOWORLD_SCENE_H__