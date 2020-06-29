#include "InGame.h"
#include "SimpleAudioEngine.h"
#include "CreatePopUnit.h"
#include "GameOver.h"
#include "Stage_clear.h"

USING_NS_CC;

using namespace cocos2d;
using namespace cocos2d::ui;

int myCoin;
int time_count;

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
	auto buy_unit_bakcUI = Sprite::create("buyUnitUi.png");
	buy_unit_bakcUI->setAnchorPoint(Vec2(0, 0));
	buy_unit_bakcUI->setScale(0.12);
	buy_unit_bakcUI->setPosition(Vec2(750, 10));
	this->addChild(buy_unit_bakcUI);

	auto label_chose_unit = Label::createWithTTF("유닛 구매", "fonts/Maplestory Light.ttf", 20);
	auto Unititem = MenuItemLabel::create(label_chose_unit, CC_CALLBACK_1(InGame::popUnit, this));
	Unititem->setColor(Color3B(0, 0, 0));
	Unititem->setAnchorPoint(ccp(1, 1)); //중심점이 우측 상단
	Unititem->setPosition(Point(winSize.width - 600, winSize.height - 770));

	auto menu = Menu::create(Unititem, NULL);
	this->addChild(menu);

	createUnit(); //초기 랜덤 캐릭터 세마리 생성

	this->schedule(schedule_selector(InGame::timer), 1.0f); //1초간격으로 tick1 작동
	
	return true;
}

void InGame::BaseFunc()
{
	//변수 초기화
	time_count = 60; //시간
	hp_count = 5; //체력
	myCoin = 0; //코인
	E_time = 50;
	B_time = 50;
	c_Xpoint = 300;
	c_Ypoint = 300;
	testPointX[0] = 100;
	testPointY[0] = 380;

	//배경
	auto back_main = Sprite::create("gameMap.png");
	back_main->setAnchorPoint(Vec2(0, 0));
	back_main->setPosition(0, 0);
	this->addChild(back_main);

	//타이머
	auto timer = Sprite::create("timer.png");
	timer->setPosition(200, 510);
	timer->setScale(0.1);
	this->addChild(timer);

	timer_label = Label::createWithTTF("30", "fonts/Maplestory Light.ttf", 20);
	timer_label->setPosition(250, 510);
	timer_label->setColor(Color3B::BLACK);
	this->addChild(timer_label);

	//레이블 수정
	timer_label->setString(StringUtils::format("%3d", time_count));

	//코인
	auto coin = Sprite::create("coin.png");
	coin->setPosition(450, 505);
	coin->setScale(0.2);
	this->addChild(coin);

	coin_label = Label::createWithTTF("0", "fonts/Maplestory Light.ttf", 20);
	coin_label->setPosition(Vec2(500, 510));
	coin_label->setColor(Color3B::BLACK);
	this->addChild(coin_label);

	//체력
	auto hp = Sprite::create("hp.png");
	hp->setPosition(680, 515);
	hp->setScale(0.09);
	this->addChild(hp);

	Hp_label = Label::createWithTTF("5", "fonts/Maplestory Light.ttf", 20);
	Hp_label->setPosition(Vec2(730, 510));
	Hp_label->setColor(Color3B::BLACK);
	this->addChild(Hp_label);

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
	coin_label->setString(StringUtils::format("%3d", myCoin));

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
	timer_label->setString(StringUtils::format("%3d", time_count)); //레이블 수정

	if (time_count == -1) //0이 보이고 1초후 게임종료
	{
		//게임 종료
		SimpleAudioEngine::getInstance()->unloadEffect("GunSound.wav"); //메모리에서 효과음 삭제
		popuplayer_stage(this); //스테이지 클리어 팝업 띄우기
	}
}

void InGame::timer_for_monsterOut(float f)
{
	//게임 종료
	SimpleAudioEngine::getInstance()->unloadEffect("GunSound.wav"); //메모리에서 효과음 삭제
	popuplayer_stage(this);//스테이지 클리어 팝업 띄우기

}

void InGame::createBullet()
{
	//indexBullet += 1;

	//SimpleAudioEngine::getInstance()->preloadEffect("GunSound.wav"); //메모리에 효과음 저장
	//SimpleAudioEngine::getInstance()->playEffect("GunSound.wav", false); //효과음출력

	//pBullet[indexBullet] = Sprite::create("ball.png");
	//pBullet[indexBullet]->setPosition(Vec2(testPointX[testCount] + 50, testPointY[testCount]));

	//this->addChild(pBullet[indexBullet]);

	////auto SmokeParticle = ParticleSmoke::create();
	////SmokeParticle->setDuration(0.1f); //출력 시간
	////SmokeParticle->setSpeed(100); //진행 시간
	////SmokeParticle->setGravity(Point(0, 300)); //y축으로 중력을 300정도 지정
	////SmokeParticle->setAutoRemoveOnFinish(true); //파티클 지속시간 종료 후 자동제거
	////SmokeParticle->setPosition(Vec2(pBullet[indexBullet]->getPositionX(), pBullet[indexBullet]->getPositionY()));
	////this->addChild(SmokeParticle);

	//auto myActionForward = MoveTo::create(1, Vec2(950, testPointY[testCount])); //정면으로 날리기
	//auto myAction = Sequence::create(Place::create(Vec2(testPointX[testCount] + 50, testPointY[testCount])), myActionForward, nullptr); //원래 위치로 바꾸기
	//pBullet[indexBullet]->runAction(myAction);

	SimpleAudioEngine::getInstance()->preloadEffect("GunSound.wav"); //메모리에 효과음 저장
	SimpleAudioEngine::getInstance()->playEffect("GunSound.wav", false); //효과음출력

	for (int indexBullet = 0; indexBullet <= testCount; ++indexBullet)
	{
		pBullet[indexBullet] = Sprite::create("ball.png");
		pBullet[indexBullet]->setPosition(Vec2(testPointX[indexBullet] + 50, testPointY[indexBullet]));

		this->addChild(pBullet[indexBullet]);

		auto myActionForward = MoveTo::create(1, Vec2(950, testPointY[indexBullet])); //정면으로 날리기
		auto myAction = Sequence::create(Place::create(Vec2(testPointX[indexBullet] + 50, testPointY[indexBullet])), myActionForward, nullptr); //원래 위치로 바꾸기
		pBullet[indexBullet]->runAction(myAction);
	}
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

	//적 랜덤 좌표 등장
	
	rnd = rand() % 4; //0~3

	if (rnd == 0) //첫번째칸
	{
		Enemy_y = 380;
	}

	if (rnd == 1) //두번째칸
	{
		Enemy_y = 300;
	}
		
	if (rnd == 2) //세번째칸
	{
		Enemy_y = 220;
	}

	if (rnd == 3) //네번째칸
	{
		Enemy_y = 140;
	}	

	Enemy_x = 900;


	//1번째 적
	pEnemy->setPosition(Point(Enemy_x, Enemy_y));
	pEnemy->setScale(0.8f);
	pEnemy->setFlipX(true);

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

	auto action_test = MoveTo::create(4, Vec2(0, Enemy_y));//왼쪽
	
	pEnemy->runAction(action_test);

	//count_enemy += 1; //적 수 증가
	//log("적의 수 : %d", count_enemy);
}

//void InGame::createEnemy2()
//{
//	auto cache2 = SpriteFrameCache::getInstance();
//	cache2->addSpriteFramesWithFile("shark.plist");
//	pEnemy2 = Sprite::createWithSpriteFrameName("s1-removebg-preview.png");
//
//	//적 랜덤 좌표 등장
//	int rnd = rand() % 4; //0~3
//
//	if (rnd == 0) //첫번째칸
//	{
//		Enemy_y = 380;
//		int rnd2 = rand() % 3 + 1;
//
//		if (rnd2 == 1) //두번째칸
//			Enemy_y2 = 300;
//		if (rnd2 == 2) //세번째칸
//			Enemy_y2 = 220;
//		if (rnd2 == 3) //네번째칸
//			Enemy_y2 = 140;
//	}
//
//	if (rnd == 1) //두번째칸
//	{
//		Enemy_y = 300;
//		int rnd2 = rand() % 4;
//
//		if (rnd == 0) //첫번째칸
//			Enemy_y2 = 380;
//		if (rnd == 1) //두번째칸
//			rnd2 = rand() % 4;
//		if (rnd == 2) //세번째칸
//			Enemy_y2 = 220;
//		if (rnd == 3) //네번째칸
//			Enemy_y2 = 140;
//	}
//
//	if (rnd == 2) //세번째칸
//	{
//		Enemy_y = 220;
//		int rnd2 = rand() % 4;
//
//		if (rnd == 0) //첫번째칸
//			Enemy_y2 = 380;
//		if (rnd == 1) //두번째칸
//			Enemy_y2 = 300;
//		if (rnd == 2) //세번째칸
//			rnd2 = rand() % 4;
//		if (rnd == 3) //네번째칸
//			Enemy_y2 = 140;
//	}
//
//	if (rnd == 3) //네번째칸
//	{
//		Enemy_y = 140;
//		int rnd2 = rand() % 3;
//
//		if (rnd == 0) //첫번째칸
//			Enemy_y2 = 380;
//		if (rnd == 1) //두번째칸
//			Enemy_y2 = 300;
//		if (rnd == 2) //세번째칸
//			Enemy_y2 = 140;
//	}
//
//	Enemy_x2 = 900;
//
//	//2번째 적
//	pEnemy2->setPosition(Point(Enemy_x2, Enemy_y2));
//	pEnemy2->setScale(0.8f);
//	pEnemy2->setFlipX(true);
//	this->addChild(pEnemy2);
//	auto animation2 = Animation::create();
//	animation2->setDelayPerUnit(0.2f);
//	for (int i = 1; i < 3; i++)
//	{
//		auto frame2 = cache2->getSpriteFrameByName(StringUtils::format("s%d-removebg-preview.png", i));
//		animation2->addSpriteFrame(frame2);
//	}
//
//	auto animate2 = Animate::create(animation2);
//	auto action2 = RepeatForever::create(animate2);
//	pEnemy2->runAction(action2);
//
//	auto action_test2 = MoveTo::create(4, Vec2(0, Enemy_y2));//왼쪽
//
//	pEnemy2->runAction(action_test2);
//}


void InGame::doBuyWindUnit(std::string tableName)
{
	if (tableName == "fish"  && testCount < 16)
	{
		indexUnit += 1;

		if (start_count)
			testCount += 1;

		//순서대로 위치하여 생성되도록 함
		testPointY[testCount] = testPointY[testCount - 1] - 80; //80만큼씩 아래로 떨어져서 생성
		testPointX[testCount] = 100; //캐릭터x값 

		if (testPointY[testCount] <= 100)
		{
			testPointY[testCount] = 380;
			/*testPointX[testCount] += 80;*/
		}

		if (testCount >= 4 && testCount != 0)
		{
			testPointX[testCount] += 80;

			if (testCount >= 8 && testCount != 0)
			{
				testPointX[testCount] += 80;

				if (testCount >= 12 && testCount != 0)
					testPointX[testCount] += 80;
			}
		}

		start_count = true;

		auto cache = SpriteFrameCache::getInstance(); // 프레임 캐시 생성 (하나만 존재하는 싱글턴 객체)
		cache->addSpriteFramesWithFile("fIsh/sprite_Fish.plist"); // 프레임캐시에 plist 정보 추가
		unitWind[indexUnit] = Sprite::createWithSpriteFrameName("sprite_Fish1.png"); // 프레임캐시에서 애니메이션 기준 이미지 생성
		unitWind[indexUnit]->setPosition(Point(testPointX[testCount], testPointY[testCount]));
		unitWind[indexUnit]->setAnchorPoint(Vec2(0.5, 0.5));
		unitWind[indexUnit]->setFlipX(true);
		this->addChild(unitWind[indexUnit]);

		auto animation = Animation::create();
		animation->setDelayPerUnit(0.3f);

		for (int i = 1; i < 10; i++) // 프레임캐시에서 이미지들을 가져와 animation에 등록
		{
			auto frame = cache->getSpriteFrameByName(StringUtils::format("sprite_Fish%d.png", i));
			animation->addSpriteFrame(frame);
		}

		auto animate = Animate::create(animation);
		auto action = RepeatForever::create(animate);
		unitWind[indexUnit]->runAction(action);
	}
	if (tableName == "grass" && testCount < 16)
	{
		indexUnit += 1;

		if(start_count)
			testCount += 1;

		//순서대로 위치하여 생성되도록 함
		testPointY[testCount] = testPointY[testCount - 1] - 80; //80만큼씩 아래로 떨어져서 생성
		testPointX[testCount] = 100; //캐릭터x값 

		if (testPointY[testCount] <= 100)
		{
			testPointY[testCount] = 380;
			/*testPointX[testCount] += 80;*/
		}

		if (testCount >= 4 && testCount != 0)
		{
			testPointX[testCount] += 80;

			if (testCount >= 8 && testCount != 0)
			{
				testPointX[testCount] += 80;

				if (testCount >= 12 && testCount != 0)
					testPointX[testCount] += 80;
			}			
		}

		start_count = true;

		auto cache = SpriteFrameCache::getInstance(); // 프레임 캐시 생성 (하나만 존재하는 싱글턴 객체)
		cache->addSpriteFramesWithFile("Grass/sprite_Grass.plist"); // 프레임캐시에 plist 정보 추가
		unitGrass[indexUnit] = Sprite::createWithSpriteFrameName("sprite_Grass1.png"); // 프레임캐시에서 애니메이션 기준 이미지 생성
		unitGrass[indexUnit]->setPosition(Point(testPointX[testCount], testPointY[testCount]));
		unitGrass[indexUnit]->setAnchorPoint(Vec2(0.5, 0.5));
		unitGrass[indexUnit]->setFlipX(true);
		this->addChild(unitGrass[indexUnit]);

		auto animation = Animation::create();
		animation->setDelayPerUnit(0.3f);

		for (int i = 1; i < 14; i++) // 프레임캐시에서 이미지들을 가져와 animation에 등록
		{
			auto frame = cache->getSpriteFrameByName(StringUtils::format("sprite_Grass%d.png", i));
			animation->addSpriteFrame(frame);
		}

		auto animate = Animate::create(animation);
		auto action = RepeatForever::create(animate);
		unitGrass[indexUnit]->runAction(action);
	}
	if (tableName == "cat"  && testCount < 16)
	{
		indexUnit += 1;

		if (start_count)
			testCount += 1;

		//순서대로 위치하여 생성되도록 함
		testPointY[testCount] = testPointY[testCount - 1] - 80; //80만큼씩 아래로 떨어져서 생성
		testPointX[testCount] = 100; //캐릭터x값 

		if (testPointY[testCount] <= 100)
		{
			testPointY[testCount] = 380;
			/*testPointX[testCount] += 80;*/
		}

		if (testCount >= 4 && testCount != 0)
		{
			testPointX[testCount] += 80;

			if (testCount >= 8 && testCount != 0)
			{
				testPointX[testCount] += 80;

				if (testCount >= 12 && testCount != 0)
					testPointX[testCount] += 80;
			}
		}

		start_count = true;

		auto cache = SpriteFrameCache::getInstance(); // 프레임 캐시 생성 (하나만 존재하는 싱글턴 객체)
		cache->addSpriteFramesWithFile("cat/sprite_Cat.plist"); // 프레임캐시에 plist 정보 추가
		unitWind[indexUnit] = Sprite::createWithSpriteFrameName("sprite_Cat1.png"); // 프레임캐시에서 애니메이션 기준 이미지 생성
		unitWind[indexUnit]->setPosition(Point(testPointX[testCount], testPointY[testCount]));
		unitWind[indexUnit]->setAnchorPoint(Vec2(0.5, 0.5));
		unitWind[indexUnit]->setFlipX(true);
		this->addChild(unitWind[indexUnit]);

		auto animation = Animation::create();
		animation->setDelayPerUnit(0.3f);

		for (int i = 1; i < 21; i++) // 프레임캐시에서 이미지들을 가져와 animation에 등록
		{
			auto frame = cache->getSpriteFrameByName(StringUtils::format("sprite_Cat%d.png", i));
			animation->addSpriteFrame(frame);
		}

		auto animate = Animate::create(animation);
		auto action = RepeatForever::create(animate);
		unitWind[indexUnit]->runAction(action);
	}
	if (tableName == "mush"  && testCount < 16)
	{
		indexUnit += 1;

		if (start_count)
			testCount += 1;

		//순서대로 위치하여 생성되도록 함
		testPointY[testCount] = testPointY[testCount - 1] - 80; //80만큼씩 아래로 떨어져서 생성
		testPointX[testCount] = 100; //캐릭터x값 

		if (testPointY[testCount] <= 100)
		{
			testPointY[testCount] = 380;
			/*testPointX[testCount] += 80;*/
		}

		if (testCount >= 4 && testCount != 0)
		{
			testPointX[testCount] += 80;

			if (testCount >= 8 && testCount != 0)
			{
				testPointX[testCount] += 80;

				if (testCount >= 12 && testCount != 0)
					testPointX[testCount] += 80;
			}
		}

		start_count = true;

		auto cache = SpriteFrameCache::getInstance(); // 프레임 캐시 생성 (하나만 존재하는 싱글턴 객체)
		cache->addSpriteFramesWithFile("Mush/sprite_Mush.plist"); // 프레임캐시에 plist 정보 추가
		unitWind[indexUnit] = Sprite::createWithSpriteFrameName("sprite_Mush1.png"); // 프레임캐시에서 애니메이션 기준 이미지 생성
		unitWind[indexUnit]->setPosition(Point(testPointX[testCount], testPointY[testCount]));
		unitWind[indexUnit]->setAnchorPoint(Vec2(0.5, 0.5));
		unitWind[indexUnit]->setFlipX(true);
		this->addChild(unitWind[indexUnit]);

		auto animation = Animation::create();
		animation->setDelayPerUnit(0.3f);

		for (int i = 1; i < 19; i++) // 프레임캐시에서 이미지들을 가져와 animation에 등록
		{
			auto frame = cache->getSpriteFrameByName(StringUtils::format("sprite_Mush%d.png", i));
			animation->addSpriteFrame(frame);
		}

		auto animate = Animate::create(animation);
		auto action = RepeatForever::create(animate);
		unitWind[indexUnit]->runAction(action);
	}
	if (tableName == "wood"  && testCount < 16)
	{
		indexUnit += 1;

		if (start_count)
			testCount += 1;

		//순서대로 위치하여 생성되도록 함
		testPointY[testCount] = testPointY[testCount - 1] - 80; //80만큼씩 아래로 떨어져서 생성
		testPointX[testCount] = 100; //캐릭터x값 

		if (testPointY[testCount] <= 100)
		{
			testPointY[testCount] = 380;
			/*testPointX[testCount] += 80;*/
		}

		if (testCount >= 4 && testCount != 0)
		{
			testPointX[testCount] += 80;

			if (testCount >= 8 && testCount != 0)
			{
				testPointX[testCount] += 80;

				if (testCount >= 12 && testCount != 0)
					testPointX[testCount] += 80;
			}
		}

		start_count = true;

		auto cache = SpriteFrameCache::getInstance(); // 프레임 캐시 생성 (하나만 존재하는 싱글턴 객체)
		cache->addSpriteFramesWithFile("Wood/sprite_Wood.plist"); // 프레임캐시에 plist 정보 추가
		unitWind[indexUnit] = Sprite::createWithSpriteFrameName("sprite_Wood1.png"); // 프레임캐시에서 애니메이션 기준 이미지 생성
		unitWind[indexUnit]->setPosition(Point(testPointX[testCount], testPointY[testCount]));
		unitWind[indexUnit]->setAnchorPoint(Vec2(0.5, 0.5));
		unitWind[indexUnit]->setFlipX(true);
		this->addChild(unitWind[indexUnit]);

		auto animation = Animation::create();
		animation->setDelayPerUnit(0.3f);

		for (int i = 1; i < 21; i++) // 프레임캐시에서 이미지들을 가져와 animation에 등록
		{
			auto frame = cache->getSpriteFrameByName(StringUtils::format("sprite_Wood%d.png", i));
			animation->addSpriteFrame(frame);
		}

		auto animate = Animate::create(animation);
		auto action = RepeatForever::create(animate);
		unitWind[indexUnit]->runAction(action);
	}
	if (tableName == "tiger"  && testCount < 16)
	{
		indexUnit += 1;

		if (start_count)
			testCount += 1;

		//순서대로 위치하여 생성되도록 함
		testPointY[testCount] = testPointY[testCount - 1] - 80; //80만큼씩 아래로 떨어져서 생성
		testPointX[testCount] = 100; //캐릭터x값 

		if (testPointY[testCount] <= 100)
		{
			testPointY[testCount] = 380;
			/*testPointX[testCount] += 80;*/
		}

		if (testCount >= 4 && testCount != 0)
		{
			testPointX[testCount] += 80;

			if (testCount >= 8 && testCount != 0)
			{
				testPointX[testCount] += 80;

				if (testCount >= 12 && testCount != 0)
					testPointX[testCount] += 80;
			}
		}

		start_count = true;

		auto cache = SpriteFrameCache::getInstance(); // 프레임 캐시 생성 (하나만 존재하는 싱글턴 객체)
		cache->addSpriteFramesWithFile("tiger/sprite_Tiger.plist"); // 프레임캐시에 plist 정보 추가
		unitWind[indexUnit] = Sprite::createWithSpriteFrameName("sprite_Tiger1.png"); // 프레임캐시에서 애니메이션 기준 이미지 생성
		unitWind[indexUnit]->setPosition(Point(testPointX[testCount], testPointY[testCount]));
		unitWind[indexUnit]->setAnchorPoint(Vec2(0.5, 0.5));
		unitWind[indexUnit]->setFlipX(true);
		this->addChild(unitWind[indexUnit]);

		auto animation = Animation::create();
		animation->setDelayPerUnit(0.3f);

		for (int i = 1; i < 23; i++) // 프레임캐시에서 이미지들을 가져와 animation에 등록
		{
			auto frame = cache->getSpriteFrameByName(StringUtils::format("sprite_Tiger%d.png", i));
			animation->addSpriteFrame(frame);
		}

		auto animate = Animate::create(animation);
		auto action = RepeatForever::create(animate);
		unitWind[indexUnit]->runAction(action);
	}

	this->schedule(schedule_selector(InGame::tick1), 0.8f); //1초간격으로 tick1 작동
}

void InGame::c_MoveToTouch()
{
	//터치 좌표 받아옴
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(InGame::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void InGame::tick1(float f)
{
	for (int indexBullet = 0; indexBullet <= testCount; ++indexBullet)
	{
		if (pBullet[indexBullet] == nullptr)
		{
			this->createBullet(); //총알 생성		
		}
	}

	if (pEnemy == nullptr)
	{
		this->createEnemy(); //적 생성
	}

	//if (pEnemy2 == nullptr)
	//{
	//	this->createEnemy2(); //적 생성
	//}


	for (int indexBullet = 0; indexBullet <= testCount; ++indexBullet)
	{
		Bullet_x[indexBullet] = pBullet[indexBullet]->getPosition().x;
		Bullet_y[indexBullet] = pBullet[indexBullet]->getPosition().y;
	}

	Enemy_x = pEnemy->getPosition().x;
	Enemy_y = pEnemy->getPosition().y;

	//Enemy_x2 = pEnemy2->getPosition().x;
	//Enemy_y2 = pEnemy2->getPosition().y;


	for (int indexBullet = 0; indexBullet <= testCount; ++indexBullet)
	{
		if ((Bullet_x[indexBullet] <= Enemy_x+ 149 && Bullet_x[indexBullet] >= Enemy_x - 149) 
			&& (Bullet_y[indexBullet] <= Enemy_y + 50 && Bullet_y[indexBullet] >= Enemy_y - 50))
		{
			SimpleAudioEngine::getInstance()->preloadEffect("Item Purchase.wav"); //메모리에 효과음 저장
			SimpleAudioEngine::getInstance()->playEffect("Item Purchase.wav", false); //효과음출력


			pBullet[indexBullet]->removeFromParentAndCleanup(true); //총알제거
			pBullet[indexBullet] = nullptr; // 일정시간 사용이 없기 전 가지는 객체정보가 남아 있으므로 반드시 nullptr로 처리해야 새로 생성가능..

			myCoin += 5;

			bChange = true;
		}

		//if ((Bullet_x[indexBullet] <= Enemy_x2 + 149 && Bullet_x[indexBullet] >= Enemy_x2 - 149)
		//	&& (Bullet_y[indexBullet] <= Enemy_y2 + 50 && Bullet_y[indexBullet] >= Enemy_y2 - 50))
		//{
		//	SimpleAudioEngine::getInstance()->preloadEffect("Item Purchase.wav"); //메모리에 효과음 저장
		//	SimpleAudioEngine::getInstance()->playEffect("Item Purchase.wav", false); //효과음출력


		//	pBullet[indexBullet]->removeFromParentAndCleanup(true); //총알제거
		//	pBullet[indexBullet] = nullptr; // 일정시간 사용이 없기 전 가지는 객체정보가 남아 있으므로 반드시 nullptr로 처리해야 새로 생성가능..

		//	myCoin += 5;
		//	coin_label->setString(StringUtils::format("%3d", myCoin)); //레이블 수정

		//	bChange2 = true;
		//}

		if (Enemy_x <= 20 && !bChange) //왼쪽 끝에 도달하면
		{
			bChange = true;

			hp_count -= 1;
			Hp_label->setString(StringUtils::format("%3d", hp_count)); //레이블 수정
		}

		//if (Enemy_x2 <= 20 && !bChange2) //왼쪽 끝에 도달하면
		//{
		//	bChange2 = true;

		//	hp_count -= 1;
		//	Hp_label->setString(StringUtils::format("%3d", hp_count)); //레이블 수정
		//}
	}
	if (bChange)
	{
		pEnemy ->removeFromParentAndCleanup(true); //적제거
		pEnemy = nullptr; // 일정시간 사용이 없기 전 가지는 객체정보가 남아 있으므로 반드시 nullptr로 처리해야 새로 생성가능..
		bChange = false;
	}

	//if (bChange2)
	//{
	//	pEnemy2->removeFromParentAndCleanup(true); //적제거
	//	pEnemy2 = nullptr; // 일정시간 사용이 없기 전 가지는 객체정보가 남아 있으므로 반드시 nullptr로 처리해야 새로 생성가능..
	//	bChange2 = false;
	//}

	if (hp_count <= 0)//사운드출력이 한번만 되어야하는데, 여러번 됨
	{
		SimpleAudioEngine::getInstance()->unloadEffect("GunSound.wav"); //메모리에서 효과음 삭제
		popuplayer(this);
	}

	for (int indexBullet = 0; indexBullet <= testCount; ++indexBullet)
	{
		 if (Bullet_x[indexBullet] >= 800)
		{
			pBullet[indexBullet]->removeFromParentAndCleanup(true); //총알제거
			pBullet[indexBullet] = nullptr; // 일정시간 사용이 없기 전 가지는 객체정보가 남아 있으므로 반드시 nullptr로 처리해야 새로 생성가능..
		}
	}


}

void InGame::popUnit(Ref* sender)
{
	SimpleAudioEngine::getInstance()->preloadEffect("Map Open.wav"); //메모리에 효과음 저장
	SimpleAudioEngine::getInstance()->playEffect("Map Open.wav", false); //효과음출력

	CreatePopUnit* popup = CreatePopUnit::create();
	this->addChild(popup, 10);

	SimpleAudioEngine::getInstance()->unloadEffect("Map Open.wav");
}

void InGame::createUnit()
{
	srand(time(NULL));

	std::string table;
	int rnd[3];

	for (int i = 0; i < 3; i++)
		rnd[i] = rand() % 3; //0~2

	for (int i = 0; i < 3; i++)
	{
		log("rand num : %d", rnd[i]);

		if (rnd[i] == 0) //0이면, 물 속성 생성
		{
			table = "fish";
			doBuyWindUnit(table);
		}
		if (rnd[i] == 1) //1이면, 땅 속성 생성
		{
			table = "grass";
			doBuyWindUnit(table);
		}
		if (rnd[i] == 2)//2이면, 불 속성 생성
		{
			table = "cat";
			doBuyWindUnit(table);
		}
	}
}

void InGame::popuplayer(Ref*sender)
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();

	CCDirector::sharedDirector()->pause(); //화면 정지

	auto layer = GameOver::create();
	layer->setScaleX(0.8);
	layer->setScaleY(0.8);
	this->addChild(layer);
}

void InGame::popuplayer_stage(Ref*sender)
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();

	CCDirector::sharedDirector()->pause(); //화면 정지

	auto layer = Stage_clear::create();
	layer->setScaleX(0.8);
	layer->setScaleY(0.8);
	this->addChild(layer);
}
