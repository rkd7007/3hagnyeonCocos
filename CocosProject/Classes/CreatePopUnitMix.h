#ifndef __CREATE_POP_UNIT_MIX_H__
#define __CREATE_POP_UNIT_MIX_H__

#include "cocos2d.h"

USING_NS_CC;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif


class CreatePopUnitMix : public cocos2d::Layer
{
public:
    virtual bool init();

	void BackInGame(Ref* sneder);
	void MixUnit(Ref* sneder, int unitNum);

    // implement the "static create()" method manually
    CREATE_FUNC(CreatePopUnitMix);
};

#endif // __HELLOWORLD_SCENE_H__