#include "InGame.h"
#include "SimpleAudioEngine.h"
#include "CreatePopUnit.h"
#include "CreatePopUnitMix.h"
#include "GameOver.h"
#include "PopAllUnit.h"

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

	//Device의 크기를 가져옵니다.
	auto winSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();

	SimpleAudioEngine::getInstance()->playBackgroundMusic("CasualGameBGM.mp3", true); //반복해서 출력

	BaseFunc();

	this->scheduleUpdate();
	
	//유닛 속성 뽑는 팝업 창 생성
	auto label_chose_unit = Label::createWithSystemFont("유닛 구매", "DAON_2.28(L)", 20);
	auto Unititem = MenuItemLabel::create(label_chose_unit, CC_CALLBACK_1(InGame::popUnit, this));
	Unititem->setColor(Color3B(0, 0, 0));
	Unititem->setAnchorPoint(ccp(1, 1)); //중심점이 우측 상단
	Unititem->setPosition(Point(winSize.width - 500, winSize.height - 300));

	//유닛 속성 조합하는 팝업 창 생성
	auto label_Mix_unit = Label::createWithSystemFont("유닛 조합", "DAON_2.28(L)", 20);
	auto UnitMixitem = MenuItemLabel::create(label_Mix_unit, CC_CALLBACK_1(InGame::popUnitMix, this));
	UnitMixitem->setColor(Color3B(0, 0, 0));
	UnitMixitem->setAnchorPoint(ccp(1, 1)); //중심점이 우측 상단
	UnitMixitem->setPosition(Point(winSize.width - 600, winSize.height - 300));

	//유닛 모음 창 생성
	auto label_All_unit = Label::createWithSystemFont("유닛", "DAON_2.28(L)", 20);
	auto UnitAllitem = MenuItemLabel::create(label_All_unit, CC_CALLBACK_1(InGame::popUnitAll, this));
	UnitAllitem->setColor(Color3B(0, 0, 0));
	UnitAllitem->setAnchorPoint(ccp(0, 0)); //중심점이 좌측 하단
	UnitAllitem->setPosition(Point(200, winSize.height - 800));

	auto menu = Menu::create(Unititem, UnitMixitem, UnitAllitem, NULL);
	//menu->setAnchorPoint(ccp(1, 1)); //중심점이 우측 상단
	//menu->setPosition(Point(winSize.width - 100, winSize.height - 50));
	//menu->alignItemsHorizontally(); //좌우병렬
	this->addChild(menu);

	createUnit(); //초기 랜덤 캐릭터 세마리 생성

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
	testPointX[0] = 100;
	testPointY[0] = 380;

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
				//10마리 이상 생성되면 오류가 남
			}
		}
	}
	else
	{
		this->schedule(schedule_selector(InGame::timer_for_monsterOut), 1.0f);
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
		//게임 종료
		SimpleAudioEngine::getInstance()->unloadEffect("GunSound.wav"); //메모리에서 효과음 삭제
		Director::getInstance()->replaceScene(GameOver::createScene()); //게임오버 씬으로 이동
	}
}


void InGame::timer_for_monsterOut(float f)
{
	//게임 종료
	SimpleAudioEngine::getInstance()->unloadEffect("GunSound.wav"); //메모리에서 효과음 삭제
	Director::getInstance()->replaceScene(GameOver::createScene()); //게임오버 씬으로 이동

}



void InGame::createBullet()
{
	indexBullet += 1;

	SimpleAudioEngine::getInstance()->preloadEffect("GunSound.wav"); //메모리에 효과음 저장
	SimpleAudioEngine::getInstance()->playEffect("GunSound.wav", false); //효과음출력

	pBullet[indexBullet] = Sprite::create("ball.png");
	pBullet[indexBullet]->setPosition(Vec2(testPointX[testCount] - 50, testPointY[testCount]));

	this->addChild(pBullet[indexBullet]);

	//auto SmokeParticle = ParticleSmoke::create();
	//SmokeParticle->setDuration(0.1f); //출력 시간
	//SmokeParticle->setSpeed(100); //진행 시간
	//SmokeParticle->setGravity(Point(0, 300)); //y축으로 중력을 300정도 지정
	//SmokeParticle->setAutoRemoveOnFinish(true); //파티클 지속시간 종료 후 자동제거
	//SmokeParticle->setPosition(Vec2(pBullet[indexBullet]->getPositionX(), pBullet[indexBullet]->getPositionY()));
	//this->addChild(SmokeParticle);

	auto myActionForward = MoveTo::create(1, Vec2(-10, testPointY[testCount])); //정면으로 날리기
	auto myAction = Sequence::create(Place::create(Vec2(testPointX[testCount] - 50, testPointY[testCount])), myActionForward, nullptr); //원래 위치로 바꾸기
	pBullet[indexBullet]->runAction(myAction);
}

bool InGame::onTouchBegan(Touch* touch, Event* event)
{
	auto touchpoint = touch->getLocation(); //터치위치알아오기
	isTouchpointX = touchpoint.x; //터치 x좌표 받아옴
	isTouchpointY = touchpoint.y; //터치 y좌표 받아옴

	return true;
}

void InGame::createEnemy()
{
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("shark.plist");
	pEnemy = Sprite::createWithSpriteFrameName("s1-removebg-preview.png");

	pEnemy->setPosition(Point(70, 450));
	pEnemy->setScale(0.8f);
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

	count_enemy += 1; //적 수 증가
	log("적의 수 : %d", count_enemy);

	//적이 100마리가 넘어가면
	if (count_enemy >= 100)
		MaxEnemy = true;
}

void InGame::doBuyWindUnit(std::string tableName)
{
	if (tableName == "wind")
	{
		log("wind 호출");
	}
	if (tableName == "ground")
	{
		log("ground 호출");
		log("x위치 : %d, y위치 : %d", testPointX[testCount], testPointY[testCount]);

		indexUnit += 1;
		testCount += 1;

		//순서대로 위치하여 생성되도록 함
		testPointY[testCount] = testPointY[testCount - 1] - 80;
		testPointX[testCount] = 100;

		if (testPointY[testCount] <= 100)
		{
			testPointY[testCount] = 380;
			testPointX[testCount] += 80;
		}

		auto cache = SpriteFrameCache::getInstance(); // 프레임 캐시 생성 (하나만 존재하는 싱글턴 객체)
		cache->addSpriteFramesWithFile("ground_Gun.plist"); // 프레임캐시에 plist 정보 추가
		unitWind[indexUnit] = Sprite::createWithSpriteFrameName("ground_Gun1.png"); // 프레임캐시에서 애니메이션 기준 이미지 생성
		unitWind[indexUnit]->setPosition(Point(testPointX[testCount], testPointY[testCount]));
		unitWind[indexUnit]->setAnchorPoint(Vec2(0.5, 0.5));
		unitWind[indexUnit]->setFlipX(true);
		this->addChild(unitWind[indexUnit]);

		auto animation = Animation::create();
		animation->setDelayPerUnit(0.3f);

		for (int i = 1; i < 6; i++) // 프레임캐시에서 이미지들을 가져와 animation에 등록
		{
			auto frame = cache->getSpriteFrameByName(StringUtils::format("ground_Gun%d.png", i));
			animation->addSpriteFrame(frame);
		}

		auto animate = Animate::create(animation);
		auto action = RepeatForever::create(animate);
		unitWind[indexUnit]->runAction(action);
	}
	if (tableName == "fire")
	{
		log("fire 호출");
	}

	this->schedule(schedule_selector(InGame::tick1), 0.8f); //1초간격으로 tick1 작동
}

void InGame::c_MoveToTouch()
{
	//터치 좌표 받아옴
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(InGame::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//if (isTouch) //&& isCreatePly
	//{
	//	//터치 위치로 옮기기 - 자연스럽지 않음
	//	//c_Xpoint = isTouchpointX;
	//	//c_Ypoint = isTouchpointY;
	//	//pPlayer->setPosition(Vec2(c_Xpoint, c_Ypoint));
	//	//isTouch = false;

	//	//터치 위치로 움직이기 - 딜레이 생김
	//	auto action = MoveTo::create(1, Vec2(isTouchpointX, isTouchpointY));
	//	c_Xpoint = isTouchpointX;
	//	c_Ypoint = isTouchpointY;
	//	auto action1 = Sequence::create(action, NULL);
	//	unitWind1->runAction(action1);
	//	isTouch = false;

	//	if (isTouchpointX < c_Xpoint)
	//	{
	//		unitWind1->setFlippedX(true);
	//	}
	//}
}

void InGame::tick1(float f)
{
	if (pBullet[indexBullet] == nullptr)
	{
		this->createBullet(); //총알 생성		
	}

	if (pEnemy == nullptr)
	{
		this->createEnemy(); //적 생성
	}

	Bullet_x = pBullet[indexBullet]->getPosition().x;
	Bullet_y = pBullet[indexBullet]->getPosition().y;

	Enemy_x = pEnemy->getPosition().x;
	Enemy_y = pEnemy->getPosition().y;

	//if (pBullet->getBoundingBox().intersectsRect(pEnemy->getBoundingBox()))//충돌하면
	if((Bullet_x <= Enemy_x +149 && Bullet_x >= Enemy_x - 149) && (Bullet_y <= Enemy_y + 50 && Bullet_y >= Enemy_y - 50))
	{
		pBullet[indexBullet]->removeFromParentAndCleanup(true); //총알제거
		pBullet[indexBullet] = nullptr; // 일정시간 사용이 없기 전 가지는 객체정보가 남아 있으므로 반드시 nullptr로 처리해야 새로 생성가능..

		score = score + 10;
		score_label->setString(StringUtils::format("Score : %3d", score)); //레이블 수정

		bChange = true;

		/*int killenemy = UserDefault::getInstance()->getIntegerForKey("KILLENEMY") + 1;
		UserDefault::getInstance()->setIntegerForKey("KILLENEMY", killenemy);
		UserDefault::getInstance()->flush();
		killenemy_label->setString(StringUtils::format("KILL : %3d", killenemy));*/

		//auto particle = ParticleGalaxy::create();
		//particle->setDuration(0.2f); //출력 시간
		//particle->setSpeed(100); //진행 시간
		//particle->setGravity(Point(0, 300)); //y축으로 중력을 300정도 지정
		//particle->setAutoRemoveOnFinish(true); //파티클 지속시간 종료 후 자동제거
		//particle->setPosition(Vec2(pEnemy->getPositionX(), pEnemy->getPositionY()));
		//this->addChild(particle);
	}

	if (bChange)
	{
		pEnemy->removeFromParentAndCleanup(true); //적제거
		pEnemy = nullptr; // 일정시간 사용이 없기 전 가지는 객체정보가 남아 있으므로 반드시 nullptr로 처리해야 새로 생성가능..

		bChange = false;
	}
	else if (Bullet_x <= -1)
	{
		pBullet[indexBullet]->removeFromParentAndCleanup(true); //총알제거
		pBullet[indexBullet] = nullptr; // 일정시간 사용이 없기 전 가지는 객체정보가 남아 있으므로 반드시 nullptr로 처리해야 새로 생성가능..
	}
}

void InGame::popUnit(Ref* sender)
{
	CreatePopUnit* popup = CreatePopUnit::create();
	this->addChild(popup, 10);

	//auto layer = CreatePopUnit::create(); //레이어 생성
	//layer->setScaleX(0.5);
	//layer->setScaleY(0.5);
	//this->addChild(layer);
}

void InGame::popUnitMix(Ref* sender)
{
	CreatePopUnitMix* popup = CreatePopUnitMix::create();
	this->addChild(popup, 10);
}

void InGame::popUnitAll(Ref* sender)
{
	PopAllUnit* popup = PopAllUnit::create();
	this->addChild(popup, 10);
}

void InGame::createUnit()
{
	srand(time(NULL));

	std::string table;
	//int rnd[3];
	int rnd[3] = { 1,1,1 }; //테스트용

	//for (int i = 0; i < 3; i++)
	//	rnd[i] = rand() % 3; //0~2

	for (int i = 0; i < 3; i++)
	{
		log("rand num : %d", rnd[i]);

		if (rnd[i] == 0) //0이면, 바람 속성 생성
		{
			if (i == 0) //첫번째 생성이면
			{
				testPointX[testCount] = 100;
				testPointY[testCount] = 380;
			}
			if (i == 1) //두번째 생성이면
			{
				testPointX[testCount] = 100;
				testPointY[testCount] = 300;
			}
			if (i == 2) //세번째 생성이면
			{
				testPointX[testCount] = 100;
				testPointY[testCount] = 220;
			}
			table = "wind";
			doBuyWindUnit(table);
		}
		if (rnd[i] == 1) //1이면, 땅 속성 생성
		{
			//맵의 작은 네모 좌표 = 최대 : x 100, y 400, 최소 : x 100, y 100
			//유닛간의 간격 = x 80, y 80

			//if (i == 0) //첫번째 생성이면
			//{
			//	testPointX[testCount] = 100;
			//	testPointY[testCount] = 380;
			//}
			//if (i == 1) //두번째 생성이면
			//{
			//	testPointX[testCount+1] = 100;
			//	testPointY[testCount+1] = 300;
			//}
			//if (i == 2) //세번째 생성이면
			//{
			//	testPointX[testCount+2] = 100;
			//	testPointY[testCount+2] = 220;
			//}
			table = "ground";
			doBuyWindUnit(table);
		}
		if (rnd[i] == 2)//2이면, 불 속성 생성
		{
			if (i == 0) //첫번째 생성이면
			{
				testPointX[testCount] = 100;
				testPointY[testCount] = 380;
			}
			if (i == 1) //두번째 생성이면
			{
				testPointX[testCount] = 100;
				testPointY[testCount] = 300;
			}
			if (i == 2) //세번째 생성이면
			{
				testPointX[testCount] = 100;
				testPointY[testCount] = 220;
			}
			table = "fire";
			doBuyWindUnit(table);
		}
	}
}