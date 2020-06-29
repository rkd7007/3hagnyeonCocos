#ifndef __Stage_clear_SCENE_H__
#define __Stage_clear_SCENE_H__

#include "cocos2d.h"
#include "TouchBtn.h"
#include "Btn_goMenu.h"
USING_NS_CC;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif


class Stage_clear : public cocos2d::Layer
{
public:
	virtual bool init();
	void SceneMove(Ref*sender);

	void GoBack(Ref * sender);
	CREATE_FUNC(Stage_clear);
};

#endif // __Stage_clear_H__