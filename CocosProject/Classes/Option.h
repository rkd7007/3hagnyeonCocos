#ifndef __OPTION_H__
#define __OPTION_H__

#include "cocos2d.h"

USING_NS_CC;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif


class Option : public cocos2d::Layer
{
public:
	virtual bool init();

	CREATE_FUNC(Option);
};

#endif // __GameOver_H__