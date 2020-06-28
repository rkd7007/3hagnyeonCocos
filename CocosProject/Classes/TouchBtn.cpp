#include "TouchBtn.h"

USING_NS_CC;


TouchBtn* TouchBtn::create(const std::string& filename)
{
	TouchBtn * sprite = new (std::nothrow) TouchBtn();
	//nothrow 는 정상적으로 TouchBtn 가 생성되지 않은 경우 프로그램이 죽지 않도록 예외처리를 해줌

	if (sprite && sprite->initWithFile(filename))
	{
		sprite->autorelease(); // 스프라이트 사용이 끝날 때 자동으로 메모리에서 제거될 수 있도록 함
		return sprite;
	}

	CC_SAFE_DELETE(sprite); // 사용이 끝난 스프라이트는 제거
	return nullptr;
}

void TouchBtn::onEnter() //화면이 출력될때 동작
{
	Sprite::onEnter(); //반드시 먼저 호출
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [=](Touch* touch, Event*event)
	{
		//onTouchBegan 내용을 람다함수로 처리 (교재 240, 터치중인 몬스터 색상 -> 빨간색(다음슬라이드))
		log("touch began");
		Vec2 LocationInNode = this->convertToNodeSpace(touch->getLocation());
		Size s = this->getContentSize(); //람다로 작업했으므로 this는 몬스터
		Rect rect = Rect(0, 0, s.width, s.height);

		if (rect.containsPoint(LocationInNode)) //해당몬스터가 터치되었는가?
		{
			this->setColor(Color3B::RED);
			
			return true;
		}
	}; //람다함수끝

	   //onTouchMoved, onTouchEnded도 람다 함수로 추가 (터치종료된 몬스터 색상->원래색 (다음슬라이드))

	listener->onTouchMoved = [=](Touch*touch, Event*event)
	{
		//this->setPosition(this->getPosition() + touch->getDelta()); //이동한 정보를 반영

		//															//move 정보를 가져와야함
		//															//lod_position = touch -> getPreviousLocation();
	};

	listener->onTouchEnded = [=](Touch * touch, Event * evnet)
	{
		exit(0);
	};



	//터치 우선순위 조정방법을 설정해봄(처음엔 false로 테트스, 몬스터 생성시 설정)

	if (_useNodePriority) //우선순위가 그려진 순서대로 이면
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this); //그려진 순서대로
	else // 우선순위를 지정된 순서로 바군다면 (처음상태)
		_eventDispatcher->addEventListenerWithFixedPriority(listener, _fixedPriority); // 지정된 우선순위대로

	_listener = listener; //화면 보일때 터치하면 리스너 만들고 화면 사라지면 리스너 제거

}

void TouchBtn::onExit()
{
	_eventDispatcher->removeEventListener(_listener); //화면이 사라질때 리스너 제거
	Sprite::onExit(); //반드시 호출
}

void TouchBtn::setPriority(int fixedPriority)
{
	//지정된 값으로 터치 우선순위를 설정하고자 할 때 호출되는 메서드
	_fixedPriority = fixedPriority;
}

void TouchBtn::setPriorityWithThis(bool usenodePriority)
{
	//터치 우선 순위를 ZORDER 순서로 할 찌, 주어신 값을 이용할지 결정하는 메소드
	_useNodePriority = usenodePriority;
}