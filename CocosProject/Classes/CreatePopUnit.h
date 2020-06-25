#ifndef __CREATE_POP_UNIT_H__
#define __CREATE_POP_UNIT_H__

#include "cocos2d.h"

USING_NS_CC;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif


class CreatePopUnit : public cocos2d::Layer
{
public:
    virtual bool init();

	void BackInGame(Ref* sneder);
	void CreateUnit(Ref* sneder, int unitNum);

	//·¹º§ 1 À¯´Ö °¹¼ö
	int wind_1;
	int ground_1;
	int fire_1;

    // implement the "static create()" method manually
    CREATE_FUNC(CreatePopUnit);
};

#endif // __HELLOWORLD_SCENE_H__