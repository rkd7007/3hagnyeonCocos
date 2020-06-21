#include "InGame.h"
#include "SimpleAudioEngine.h"
#include "CreatePopUnit.h"

using namespace cocos2d;

//오디오 소스 관련 네임스페이스 선언
using namespace CocosDenshion;

Scene* InGame::createScene()
{
	return InGame::create();
}

bool InGame::init()
{
	if (!Scene::init())
	{
		return false;
	}

	SimpleAudioEngine::getInstance()->playBackgroundMusic("CasualGameBGM.mp3", true); //반복해서 출력

	BaseFunc();
	this->scheduleUpdate();

	/*
	//바람속성유닛구매 메뉴
	auto label_Unit_wind = Label::createWithSystemFont("바람 속성", "DAON_2.28(L)", 30);
	auto Unititem1 = MenuItemLabel::create(label_Unit_wind, CC_CALLBACK_1(InGame::doBuyWindUnit, this));
	Unititem1->setColor(Color3B(0, 0, 0));
	Unititem1->setAnchorPoint(Vec2(0.5, 0.5)); 
	Unititem1->setPosition(Vec2(100, 240)); 


	//땅속성유닛구매 메뉴
	auto label_Unit_ground = Label::createWithSystemFont("땅 속성", "DAON_2.28(L)", 30);
	auto Unititem2 = MenuItemLabel::create(label_Unit_ground, CC_CALLBACK_1(InGame::doBuyWindUnit, this));
	Unititem2->setColor(Color3B(0, 0, 0));
	Unititem2->setAnchorPoint(Vec2(0.5, 0.5)); 
	Unititem2->setPosition(Vec2(260, 240)); 


	//물속성유닛구매 메뉴
	auto label_Unit_water = Label::createWithSystemFont("물 속성", "DAON_2.28(L)", 30);
	auto Unititem3 = MenuItemLabel::create(label_Unit_water, CC_CALLBACK_1(InGame::doBuyWindUnit, this));
	Unititem3->setColor(Color3B(0, 0, 0));
	Unititem3->setAnchorPoint(Vec2(0.5, 0.5));
	Unititem3->setPosition(Vec2(400, 240));

	auto menu = Menu::create(Unititem1, Unititem2, Unititem3, NULL);
	this->addChild(menu);
	*/
	
	//유닛 속성 뽑는 팝업 창 생성
	auto label_chose_unit = Label::createWithSystemFont("menu", "DAON_2.28(L)", 30);
	auto Unititem = MenuItemLabel::create(label_chose_unit, CC_CALLBACK_1(InGame::poplayer, this));
	Unititem->setColor(Color3B(0, 0, 0));
	Unititem->setAnchorPoint(Vec2(0.5, 0.5));
	Unititem->setPosition(Vec2(400, 240));

	auto menu = Menu::create(Unititem, NULL);
	this->addChild(menu);

	this->schedule(schedule_selector(InGame::timer), 1.0f); //1초간격으로 tick1 작동

	return true;
}


void InGame::BaseFunc()
{
	//변수 초기화
	time_count = 60; //시간
	E_time = 50;
	B_time = 50;
	c_Xpoint = 300;
	c_Ypoint = 300;
	score = 0; //점수
	isTouch = false;

	//배경
	auto back_main = Sprite::create("back_main.png");
	back_main->setAnchorPoint(Vec2(0, 0));
	back_main->setPosition(0, 0);
	this->addChild(back_main);

	//타이머
	timer_label = Label::createWithSystemFont("Time : ", "DAON_2.28(L)", 30);
	timer_label->setPosition(90, 510);
	timer_label->setColor(Color3B::BLACK);
	this->addChild(timer_label);

	//레이블 수정
	timer_label->setString(StringUtils::format("Time : %3d", time_count));

	//점수
	score_label = Label::createWithSystemFont("Score : ", "DAON_2.28(L)", 30);
	score_label->setPosition(Vec2(270, 510));
	score_label->setColor(Color3B::BLACK);
	this->addChild(score_label);

	//죽인 적의 수
	//killenemy_label = Label::createWithSystemFont("kill : ", "DAON_2.28(L)", 30);
	//killenemy_label->setPosition(Vec2(400, 510));
	//killenemy_label->setColor(Color3B::BLACK);
	//this->addChild(killenemy_label);

	//스테이지 바꿈
	//auto item = MenuItemFont::create("STAGE", CC_CALLBACK_1(InGame::changeScene, this));
	//item->setColor(Color3B::BLACK);
	//auto menu = Menu::create(item, NULL);
	//menu->setPosition(Vec2(900, 30));
	//menu->alignItemsHorizontally();
	//this->addChild(menu);
}

void InGame::update(float f)
{
	this->E_time -= f;
	this->B_time -= f;

	this->c_MoveToTouch();
	//this->HitEnemy();

	if (!MaxEnemy)
	{
		if (this->E_time <= 0)
		{
			this->E_time = 50;

			count_enemy += 1;

			//this->createEnemy();

			if (count_enemy >= 10) //10마리 생성
			{
				//this->unscheduleUpdate();
				MaxEnemy = true;
			}
		}
	}
	if (this->B_time <= 0)
	{
		this->B_time = 50;

	}
}

void InGame::timer(float f)
{	
	time_count = time_count -1;
	timer_label->setString(StringUtils::format("Time : %3d", time_count)); //레이블 수정

	if (time_count == -1) //0이 보이고 1초후 게임종료
	{
		//게임 종료 화면 나오게 조정...
		/*auto layer = GameLayer::create();
		layer->setScaleX(0.8);
		layer->setScaleY(0.8);
		this->addChild(layer);*/

		SimpleAudioEngine::getInstance()->unloadEffect("GunSound.wav"); //메모리에서 효과음 삭제
		//exit(0);
	}
}

void InGame::createBullet()
{
	SimpleAudioEngine::getInstance()->preloadEffect("GunSound.wav"); //메모리에 효과음 저장
	SimpleAudioEngine::getInstance()->playEffect("GunSound.wav", false); //효과음출력

	pBullet = Sprite::create("ball.png");
	pBullet->setPosition(Vec2(c_Xpoint - 50, c_Ypoint));

	this->addChild(pBullet);

	auto SmokeParticle = ParticleSmoke::create();
	SmokeParticle->setDuration(0.1f); //출력 시간
	SmokeParticle->setSpeed(100); //진행 시간
	SmokeParticle->setGravity(Point(0, 300)); //y축으로 중력을 300정도 지정
	SmokeParticle->setAutoRemoveOnFinish(true); //파티클 지속시간 종료 후 자동제거
	SmokeParticle->setPosition(Vec2(pBullet->getPositionX(), pBullet->getPositionY()));
	this->addChild(SmokeParticle);

	auto myActionForward = MoveTo::create(1, Vec2(-10, c_Ypoint)); //정면으로 날리기
	auto myAction = Sequence::create(Place::create(Vec2(c_Xpoint - 50, c_Ypoint)), myActionForward, nullptr); //원래 위치로 바꾸기
	pBullet->runAction(myAction);
}


bool InGame::onTouchBegan(Touch* touch, Event* event)
{
	auto touchpoint = touch->getLocation(); //터치위치알아오기
	isTouchpointX = touchpoint.x; //터치 x좌표 받아옴
	isTouchpointY = touchpoint.y; //터치 y좌표 받아옴
	isTouch = true;

	return true;
}


void InGame::createEnemy()
{
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("shark.plist");
	pEnemy = Sprite::createWithSpriteFrameName("s1-removebg-preview.png");

	pEnemy->setPosition(Point(70, 450));

	this->addChild(pEnemy);
	auto animation = Animation::create();
	animation->setDelayPerUnit(0.2f);

	for (int i = 1; i < 3; i++)
	{
		auto frame = cache->getSpriteFrameByName(StringUtils::format("s%d-removebg-preview.png", i));
		animation->addSpriteFrame(frame);
	}

	auto animate = Animate::create(animation);
	auto action = RepeatForever::create(animate);
	pEnemy->runAction(action);

	auto action1 = MoveTo::create(3, Vec2(70, 50));//아래
	auto action2 = MoveTo::create(5, Vec2(900, 50));//오른쪽
	auto action3 = MoveTo::create(3, Vec2(900, 450));//위
	auto action4 = MoveTo::create(5, Vec2(70, 450));//왼쪽
	auto action5 = Sequence::create(action1, action2, action3, action4, NULL);
	auto action6 = RepeatForever::create(action5); //계속 반복시킴
	pEnemy->runAction(action6);
}

void InGame::doBuyWindUnit(Ref*pSender)
{
	//레이블에서 누른 것이 바람 속성이면
	auto test = Label::create();

	//레이블에서 누른 것이 땅 속성이면


	//레이블에서 누른 것이 불 속성이면

	auto cache = SpriteFrameCache::getInstance(); // 프레임 캐시 생성 (하나만 존재하는 싱글턴 객체)
	cache->addSpriteFramesWithFile("ground_Gun.plist"); // 프레임캐시에 plist 정보 추가
	unitWind1 = Sprite::createWithSpriteFrameName("ground_Gun1.png"); // 프레임캐시에서 애니메이션 기준 이미지 생성

	unitWind1->setPosition(Point(500, 500));
	unitWind1->setAnchorPoint(Vec2(0.5, 0.5));
	this->addChild(unitWind1);

	auto animation = Animation::create();
	animation->setDelayPerUnit(0.3f);

	for (int i = 1; i < 6; i++) // 프레임캐시에서 이미지들을 가져와 animation에 등록
	{
		auto frame = cache->getSpriteFrameByName(StringUtils::format("ground_Gun%d.png", i));
		animation->addSpriteFrame(frame);
	}

	auto animate = Animate::create(animation);
	auto action = RepeatForever::create(animate);
	unitWind1->runAction(action);

	this->schedule(schedule_selector(InGame::tick1), 0.8f); //1초간격으로 tick1 작동
}

void InGame::c_MoveToTouch()
{
	//터치 좌표 받아옴
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(InGame::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	if (isTouch) //&& isCreatePly
	{
		//터치 위치로 옮기기 - 자연스럽지 않음
		//c_Xpoint = isTouchpointX;
		//c_Ypoint = isTouchpointY;
		//pPlayer->setPosition(Vec2(c_Xpoint, c_Ypoint));
		//isTouch = false;

		//터치 위치로 움직이기 - 딜레이 생김
		auto action = MoveTo::create(1, Vec2(isTouchpointX, isTouchpointY));
		c_Xpoint = isTouchpointX;
		c_Ypoint = isTouchpointY;
		auto action1 = Sequence::create(action, NULL);
		unitWind1->runAction(action1);
		isTouch = false;

		if (isTouchpointX < c_Xpoint)
		{
			unitWind1->setFlippedX(true);
		}
	}
}

void InGame::tick1(float f)
{
	if (pBullet == nullptr)
	{
		this->createBullet(); //총알 생성		
	}

	if (pEnemy == nullptr)
	{
		this->createEnemy(); //적 생성
	}

	Bullet_x = pBullet->getPosition().x;
	Bullet_y = pBullet->getPosition().y;

	Enemy_x = pEnemy->getPosition().x;
	Enemy_y = pEnemy->getPosition().y;

	//if (pBullet->getBoundingBox().intersectsRect(pEnemy->getBoundingBox()))//충돌하면
	if((Bullet_x <= Enemy_x +149 && Bullet_x >= Enemy_x - 149) && (Bullet_y <= Enemy_y + 50 && Bullet_y >= Enemy_y - 50))
	{
		pBullet->removeFromParentAndCleanup(true); //총알제거
		pBullet = nullptr; // 일정시간 사용이 없기 전 가지는 객체정보가 남아 있으므로 반드시 nullptr로 처리해야 새로 생성가능..

		score = score + 10;
		score_label->setString(StringUtils::format("Score : %3d", score)); //레이블 수정

		bChange = true;

		/*int killenemy = UserDefault::getInstance()->getIntegerForKey("KILLENEMY") + 1;
		UserDefault::getInstance()->setIntegerForKey("KILLENEMY", killenemy);
		UserDefault::getInstance()->flush();

		killenemy_label->setString(StringUtils::format("KILL : %3d", killenemy));*/

		auto particle = ParticleGalaxy::create();
		particle->setDuration(0.2f); //출력 시간
		particle->setSpeed(100); //진행 시간
		particle->setGravity(Point(0, 300)); //y축으로 중력을 300정도 지정
		particle->setAutoRemoveOnFinish(true); //파티클 지속시간 종료 후 자동제거
		particle->setPosition(Vec2(pEnemy->getPositionX(), pEnemy->getPositionY()));
		this->addChild(particle);
	}

	if (bChange)
	{
		pEnemy->removeFromParentAndCleanup(true); //총알제거
		pEnemy = nullptr; // 일정시간 사용이 없기 전 가지는 객체정보가 남아 있으므로 반드시 nullptr로 처리해야 새로 생성가능..

		bChange = false;
	}

	else if (Bullet_x <= -1)
	{
		pBullet->removeFromParentAndCleanup(true); //총알제거
		pBullet = nullptr; // 일정시간 사용이 없기 전 가지는 객체정보가 남아 있으므로 반드시 nullptr로 처리해야 새로 생성가능..
	}
}

void InGame::poplayer(Ref* sender)
{
	auto layer = CreatePopUnit::create(); //레이어 생성
	layer->setScaleX(0.5);
	layer->setScaleY(0.5);
	this->addChild(layer);
}

void InGame::createPlayer()
{

}