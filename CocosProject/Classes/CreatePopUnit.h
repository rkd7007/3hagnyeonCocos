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

	bool isWind;
	bool isFire;
	bool isGround;

	void BackInGame(Ref* sneder);
	void ChagneWindBool(Ref* sneder); //¹Ù¶÷ ¼Ó¼º ´­·¶À¸¸é
	void ChagneFireBool(Ref* sneder); //ºÒ ¼Ó¼º ´­·¶À¸¸é
	void ChagneGroundBool(Ref* sneder); //¶¥ ¼Ó¼º ´­·¶À¸¸é

    // implement the "static create()" method manually
    CREATE_FUNC(CreatePopUnit);
};

#endif // __HELLOWORLD_SCENE_H__