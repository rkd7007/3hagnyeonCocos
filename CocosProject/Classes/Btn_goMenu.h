#pragma once
#include "cocos2d.h"

class Btn_goMenu : public cocos2d::Sprite //Sprite를 상속받음
{
public:
	static Btn_goMenu* create(const std::string & filename);
	void setPriority(int fixedPriority);
	void setPriorityWithThis(bool useNodePriority);

	//화면이 보이거나 사라질 때 호출
	void onEnter();
	void onExit();

	int touchCount = 0;



private:
	cocos2d::EventListener* _listener; // 몬스터가 터치처리
	int _fixedPriority; //터치우선순위 조정용
	bool _useNodePriority; // 우선순위를 정하는 방법(2가지)

}; //터치처리함수는 람다로 처리할 예정