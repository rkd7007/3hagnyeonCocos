#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "InGame.h"

USING_NS_CC;

//오디오 소스 관련 네임스페이스 선언
using namespace CocosDenshion;

Scene* HelloWorld::createScene()
{
	return HelloWorld::create();
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	SimpleAudioEngine::getInstance()->playBackgroundMusic("MainSound.mp3", true); //반복해서 출력
	createBackground();

	auto listener = EventListenerTouchOneByOne::create(); //이벤트 리스너 생성
	listener->setSwallowTouches(true);

	//처리가 끝난 터치는 이벤트에서 제거됨(z-order가 높은 오브젝트가 터치 이벤트를 수신하여 처리)
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this); //필요한 콜백함수 등록

																			//리스너를 이벤트디스패쳐에 등록
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this); //this는 현재씬의미, 화면에 그려진 순서대로 처리

	return true;
}

void HelloWorld::createBackground()
{
	auto voidNode = Layer::create();
	auto back1 = Sprite::create("MenuBack.png");
	back1->setAnchorPoint(Vec2(0, 0));
	back1->setPosition(Vec2(-20, 0));
	back1->setScaleX(1.08f);
	back1->setScaleY(1.053f);

	auto backLetter = Sprite::create("tapAny.png");
	backLetter->setAnchorPoint(Vec2(0, 0));
	backLetter->setPosition(Vec2(280, 30));
	backLetter->setScaleX(1.5f);

	auto blinkAction = Blink::create(0.9f, 1);
	auto repeatAction = RepeatForever::create(blinkAction);

	backLetter->runAction(repeatAction);

	auto back_Title = Sprite::create("back_Title.png");
	back_Title->setAnchorPoint(Vec2(0, 0));
	back_Title->setPosition(Vec2(120, 300));
	back_Title->setScale(2.0);

	//배경노드에 스프라이트를 넣는다
	voidNode->addChild(back1);

	//배경노드에 스프라이트를 넣는다
	voidNode->addChild(backLetter);

	//배경노드에 스프라이트를 넣는다
	voidNode->addChild(back_Title);

	//캐릭터보다 아래에 위치하도록 ZOrder 추가
	this->addChild(voidNode, 0);	
}

bool HelloWorld::onTouchBegan(Touch*touch, Event *event)
{

	//터치 시 화면전환
	Director::getInstance()->replaceScene(InGame::createScene());


	return true;
}


//
//void HelloWorld::tick1(float f)
//{
//	if (pBullet == nullptr)
//	{
//		this->createBullet(); //총알 생성      
//	}
//
//	if (pEnemy == nullptr)
//	{
//		this->createEnemy(); //적 생성
//	}
//
//
//	Bullet_x = pBullet->getPosition().x;
//	Bullet_y = pBullet->getPosition().y;
//
//	Enemy_x = pEnemy->getPosition().x;
//	Enemy_y = pEnemy->getPosition().y;
//
//	if ((Bullet_x <= Enemy_x+100 && Bullet_x >= Enemy_x - 100) && (Bullet_y <= Enemy_y + 200 && Bullet_y >= Enemy_y - 200))//충돌하면
//	{
//		pBullet->removeFromParentAndCleanup(true); //총알제거
//		pBullet = nullptr; // 일정시간 사용이 없기 전 가지는 객체정보가 남아 있으므로 반드시 nullptr로 처리해야 새로 생성가능..
//
//		score = score + 10;
//		score_label->setString(StringUtils::format("점수 : %3d", score)); //레이블 수정
//
//		bChange = true;
//	}
//
//	if (bChange)
//	{
//		pEnemy->removeFromParentAndCleanup(true); //총알제거
//		pEnemy = nullptr; // 일정시간 사용이 없기 전 가지는 객체정보가 남아 있으므로 반드시 nullptr로 처리해야 새로 생성가능..
//
//		bChange = false;
//	}
//
//
//	if (Bullet_x <= 0)
//	{
//		pBullet->removeFromParentAndCleanup(true); //총알제거
//		pBullet = nullptr; // 일정시간 사용이 없기 전 가지는 객체정보가 남아 있으므로 반드시 nullptr로 처리해야 새로 생성가능..
//	}
//
//}