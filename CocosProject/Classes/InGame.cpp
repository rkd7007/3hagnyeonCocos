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

//����� �ҽ� ���� ���ӽ����̽� ���� 
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

	//Device�� ũ�⸦ �����ɴϴ�.
	auto winSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();

	SimpleAudioEngine::getInstance()->playBackgroundMusic("CasualGameBGM.mp3", true); //�ݺ��ؼ� ���

	BaseFunc();

	this->scheduleUpdate();
	
	//���� �Ӽ� �̴� �˾� â ����
	auto buy_unit_bakcUI = Sprite::create("buyUnitUi.png");
	buy_unit_bakcUI->setAnchorPoint(Vec2(0, 0));
	buy_unit_bakcUI->setScale(0.12);
	buy_unit_bakcUI->setPosition(Vec2(750, 10));
	this->addChild(buy_unit_bakcUI);

	auto label_chose_unit = Label::createWithTTF("���� ����", "fonts/Maplestory Light.ttf", 20);
	auto Unititem = MenuItemLabel::create(label_chose_unit, CC_CALLBACK_1(InGame::popUnit, this));
	Unititem->setColor(Color3B(0, 0, 0));
	Unititem->setAnchorPoint(ccp(1, 1)); //�߽����� ���� ���
	Unititem->setPosition(Point(winSize.width - 600, winSize.height - 770));

	auto menu = Menu::create(Unititem, NULL);
	this->addChild(menu);

	createUnit(); //�ʱ� ���� ĳ���� ������ ����

	this->schedule(schedule_selector(InGame::timer), 1.0f); //1�ʰ������� tick1 �۵�
	
	return true;
}

void InGame::BaseFunc()
{
	//���� �ʱ�ȭ
	time_count = 60; //�ð�
	hp_count = 5; //ü��
	myCoin = 0; //����
	E_time = 50;
	B_time = 50;
	c_Xpoint = 300;
	c_Ypoint = 300;
	testPointX[0] = 100;
	testPointY[0] = 380;

	//���
	auto back_main = Sprite::create("gameMap.png");
	back_main->setAnchorPoint(Vec2(0, 0));
	back_main->setPosition(0, 0);
	this->addChild(back_main);

	//Ÿ�̸�
	auto timer = Sprite::create("timer.png");
	timer->setPosition(200, 510);
	timer->setScale(0.1);
	this->addChild(timer);

	timer_label = Label::createWithTTF("30", "fonts/Maplestory Light.ttf", 20);
	timer_label->setPosition(250, 510);
	timer_label->setColor(Color3B::BLACK);
	this->addChild(timer_label);

	//���̺� ����
	timer_label->setString(StringUtils::format("%3d", time_count));

	//����
	auto coin = Sprite::create("coin.png");
	coin->setPosition(450, 505);
	coin->setScale(0.2);
	this->addChild(coin);

	coin_label = Label::createWithTTF("0", "fonts/Maplestory Light.ttf", 20);
	coin_label->setPosition(Vec2(500, 510));
	coin_label->setColor(Color3B::BLACK);
	this->addChild(coin_label);

	//ü��
	auto hp = Sprite::create("hp.png");
	hp->setPosition(680, 515);
	hp->setScale(0.09);
	this->addChild(hp);

	Hp_label = Label::createWithTTF("5", "fonts/Maplestory Light.ttf", 20);
	Hp_label->setPosition(Vec2(730, 510));
	Hp_label->setColor(Color3B::BLACK);
	this->addChild(Hp_label);

	//���� ���� ��
	//killenemy_label = Label::createWithSystemFont("kill : ", "DAON_2.28(L)", 30);
	//killenemy_label->setPosition(Vec2(400, 510));
	//killenemy_label->setColor(Color3B::BLACK);
	//this->addChild(killenemy_label);

	//�������� �ٲ�
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

			if (count_enemy >= 10) //10���� ����
			{
				//this->unscheduleUpdate();
				MaxEnemy = true;
				//10���� �̻� �����Ǹ� ������ ��
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
	timer_label->setString(StringUtils::format("%3d", time_count)); //���̺� ����

	if (time_count == -1) //0�� ���̰� 1���� ��������
	{
		//���� ����
		SimpleAudioEngine::getInstance()->unloadEffect("GunSound.wav"); //�޸𸮿��� ȿ���� ����
		popuplayer_stage(this); //�������� Ŭ���� �˾� ����
	}
}

void InGame::timer_for_monsterOut(float f)
{
	//���� ����
	SimpleAudioEngine::getInstance()->unloadEffect("GunSound.wav"); //�޸𸮿��� ȿ���� ����
	popuplayer_stage(this);//�������� Ŭ���� �˾� ����

}

void InGame::createBullet()
{
	//indexBullet += 1;

	//SimpleAudioEngine::getInstance()->preloadEffect("GunSound.wav"); //�޸𸮿� ȿ���� ����
	//SimpleAudioEngine::getInstance()->playEffect("GunSound.wav", false); //ȿ�������

	//pBullet[indexBullet] = Sprite::create("ball.png");
	//pBullet[indexBullet]->setPosition(Vec2(testPointX[testCount] + 50, testPointY[testCount]));

	//this->addChild(pBullet[indexBullet]);

	////auto SmokeParticle = ParticleSmoke::create();
	////SmokeParticle->setDuration(0.1f); //��� �ð�
	////SmokeParticle->setSpeed(100); //���� �ð�
	////SmokeParticle->setGravity(Point(0, 300)); //y������ �߷��� 300���� ����
	////SmokeParticle->setAutoRemoveOnFinish(true); //��ƼŬ ���ӽð� ���� �� �ڵ�����
	////SmokeParticle->setPosition(Vec2(pBullet[indexBullet]->getPositionX(), pBullet[indexBullet]->getPositionY()));
	////this->addChild(SmokeParticle);

	//auto myActionForward = MoveTo::create(1, Vec2(950, testPointY[testCount])); //�������� ������
	//auto myAction = Sequence::create(Place::create(Vec2(testPointX[testCount] + 50, testPointY[testCount])), myActionForward, nullptr); //���� ��ġ�� �ٲٱ�
	//pBullet[indexBullet]->runAction(myAction);

	SimpleAudioEngine::getInstance()->preloadEffect("GunSound.wav"); //�޸𸮿� ȿ���� ����
	SimpleAudioEngine::getInstance()->playEffect("GunSound.wav", false); //ȿ�������

	for (int indexBullet = 0; indexBullet <= testCount; ++indexBullet)
	{
		pBullet[indexBullet] = Sprite::create("ball.png");
		pBullet[indexBullet]->setPosition(Vec2(testPointX[indexBullet] + 50, testPointY[indexBullet]));

		this->addChild(pBullet[indexBullet]);

		auto myActionForward = MoveTo::create(1, Vec2(950, testPointY[indexBullet])); //�������� ������
		auto myAction = Sequence::create(Place::create(Vec2(testPointX[indexBullet] + 50, testPointY[indexBullet])), myActionForward, nullptr); //���� ��ġ�� �ٲٱ�
		pBullet[indexBullet]->runAction(myAction);
	}
}

bool InGame::onTouchBegan(Touch* touch, Event* event)
{
	auto touchpoint = touch->getLocation(); //��ġ��ġ�˾ƿ���
	isTouchpointX = touchpoint.x; //��ġ x��ǥ �޾ƿ�
	isTouchpointY = touchpoint.y; //��ġ y��ǥ �޾ƿ�

	return true;
}

void InGame::createEnemy()
{
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("shark.plist");
	pEnemy = Sprite::createWithSpriteFrameName("s1-removebg-preview.png");

	//�� ���� ��ǥ ����
	
	rnd = rand() % 4; //0~3

	if (rnd == 0) //ù��°ĭ
	{
		Enemy_y = 380;
	}

	if (rnd == 1) //�ι�°ĭ
	{
		Enemy_y = 300;
	}
		
	if (rnd == 2) //����°ĭ
	{
		Enemy_y = 220;
	}

	if (rnd == 3) //�׹�°ĭ
	{
		Enemy_y = 140;
	}	

	Enemy_x = 900;


	//1��° ��
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

	auto action_test = MoveTo::create(4, Vec2(0, Enemy_y));//����
	
	pEnemy->runAction(action_test);

	//count_enemy += 1; //�� �� ����
	//log("���� �� : %d", count_enemy);
}

//void InGame::createEnemy2()
//{
//	auto cache2 = SpriteFrameCache::getInstance();
//	cache2->addSpriteFramesWithFile("shark.plist");
//	pEnemy2 = Sprite::createWithSpriteFrameName("s1-removebg-preview.png");
//
//	//�� ���� ��ǥ ����
//	int rnd = rand() % 4; //0~3
//
//	if (rnd == 0) //ù��°ĭ
//	{
//		Enemy_y = 380;
//		int rnd2 = rand() % 3 + 1;
//
//		if (rnd2 == 1) //�ι�°ĭ
//			Enemy_y2 = 300;
//		if (rnd2 == 2) //����°ĭ
//			Enemy_y2 = 220;
//		if (rnd2 == 3) //�׹�°ĭ
//			Enemy_y2 = 140;
//	}
//
//	if (rnd == 1) //�ι�°ĭ
//	{
//		Enemy_y = 300;
//		int rnd2 = rand() % 4;
//
//		if (rnd == 0) //ù��°ĭ
//			Enemy_y2 = 380;
//		if (rnd == 1) //�ι�°ĭ
//			rnd2 = rand() % 4;
//		if (rnd == 2) //����°ĭ
//			Enemy_y2 = 220;
//		if (rnd == 3) //�׹�°ĭ
//			Enemy_y2 = 140;
//	}
//
//	if (rnd == 2) //����°ĭ
//	{
//		Enemy_y = 220;
//		int rnd2 = rand() % 4;
//
//		if (rnd == 0) //ù��°ĭ
//			Enemy_y2 = 380;
//		if (rnd == 1) //�ι�°ĭ
//			Enemy_y2 = 300;
//		if (rnd == 2) //����°ĭ
//			rnd2 = rand() % 4;
//		if (rnd == 3) //�׹�°ĭ
//			Enemy_y2 = 140;
//	}
//
//	if (rnd == 3) //�׹�°ĭ
//	{
//		Enemy_y = 140;
//		int rnd2 = rand() % 3;
//
//		if (rnd == 0) //ù��°ĭ
//			Enemy_y2 = 380;
//		if (rnd == 1) //�ι�°ĭ
//			Enemy_y2 = 300;
//		if (rnd == 2) //����°ĭ
//			Enemy_y2 = 140;
//	}
//
//	Enemy_x2 = 900;
//
//	//2��° ��
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
//	auto action_test2 = MoveTo::create(4, Vec2(0, Enemy_y2));//����
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

		//������� ��ġ�Ͽ� �����ǵ��� ��
		testPointY[testCount] = testPointY[testCount - 1] - 80; //80��ŭ�� �Ʒ��� �������� ����
		testPointX[testCount] = 100; //ĳ����x�� 

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

		auto cache = SpriteFrameCache::getInstance(); // ������ ĳ�� ���� (�ϳ��� �����ϴ� �̱��� ��ü)
		cache->addSpriteFramesWithFile("fIsh/sprite_Fish.plist"); // ������ĳ�ÿ� plist ���� �߰�
		unitWind[indexUnit] = Sprite::createWithSpriteFrameName("sprite_Fish1.png"); // ������ĳ�ÿ��� �ִϸ��̼� ���� �̹��� ����
		unitWind[indexUnit]->setPosition(Point(testPointX[testCount], testPointY[testCount]));
		unitWind[indexUnit]->setAnchorPoint(Vec2(0.5, 0.5));
		unitWind[indexUnit]->setFlipX(true);
		this->addChild(unitWind[indexUnit]);

		auto animation = Animation::create();
		animation->setDelayPerUnit(0.3f);

		for (int i = 1; i < 10; i++) // ������ĳ�ÿ��� �̹������� ������ animation�� ���
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

		//������� ��ġ�Ͽ� �����ǵ��� ��
		testPointY[testCount] = testPointY[testCount - 1] - 80; //80��ŭ�� �Ʒ��� �������� ����
		testPointX[testCount] = 100; //ĳ����x�� 

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

		auto cache = SpriteFrameCache::getInstance(); // ������ ĳ�� ���� (�ϳ��� �����ϴ� �̱��� ��ü)
		cache->addSpriteFramesWithFile("Grass/sprite_Grass.plist"); // ������ĳ�ÿ� plist ���� �߰�
		unitGrass[indexUnit] = Sprite::createWithSpriteFrameName("sprite_Grass1.png"); // ������ĳ�ÿ��� �ִϸ��̼� ���� �̹��� ����
		unitGrass[indexUnit]->setPosition(Point(testPointX[testCount], testPointY[testCount]));
		unitGrass[indexUnit]->setAnchorPoint(Vec2(0.5, 0.5));
		unitGrass[indexUnit]->setFlipX(true);
		this->addChild(unitGrass[indexUnit]);

		auto animation = Animation::create();
		animation->setDelayPerUnit(0.3f);

		for (int i = 1; i < 14; i++) // ������ĳ�ÿ��� �̹������� ������ animation�� ���
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

		//������� ��ġ�Ͽ� �����ǵ��� ��
		testPointY[testCount] = testPointY[testCount - 1] - 80; //80��ŭ�� �Ʒ��� �������� ����
		testPointX[testCount] = 100; //ĳ����x�� 

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

		auto cache = SpriteFrameCache::getInstance(); // ������ ĳ�� ���� (�ϳ��� �����ϴ� �̱��� ��ü)
		cache->addSpriteFramesWithFile("cat/sprite_Cat.plist"); // ������ĳ�ÿ� plist ���� �߰�
		unitWind[indexUnit] = Sprite::createWithSpriteFrameName("sprite_Cat1.png"); // ������ĳ�ÿ��� �ִϸ��̼� ���� �̹��� ����
		unitWind[indexUnit]->setPosition(Point(testPointX[testCount], testPointY[testCount]));
		unitWind[indexUnit]->setAnchorPoint(Vec2(0.5, 0.5));
		unitWind[indexUnit]->setFlipX(true);
		this->addChild(unitWind[indexUnit]);

		auto animation = Animation::create();
		animation->setDelayPerUnit(0.3f);

		for (int i = 1; i < 21; i++) // ������ĳ�ÿ��� �̹������� ������ animation�� ���
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

		//������� ��ġ�Ͽ� �����ǵ��� ��
		testPointY[testCount] = testPointY[testCount - 1] - 80; //80��ŭ�� �Ʒ��� �������� ����
		testPointX[testCount] = 100; //ĳ����x�� 

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

		auto cache = SpriteFrameCache::getInstance(); // ������ ĳ�� ���� (�ϳ��� �����ϴ� �̱��� ��ü)
		cache->addSpriteFramesWithFile("Mush/sprite_Mush.plist"); // ������ĳ�ÿ� plist ���� �߰�
		unitWind[indexUnit] = Sprite::createWithSpriteFrameName("sprite_Mush1.png"); // ������ĳ�ÿ��� �ִϸ��̼� ���� �̹��� ����
		unitWind[indexUnit]->setPosition(Point(testPointX[testCount], testPointY[testCount]));
		unitWind[indexUnit]->setAnchorPoint(Vec2(0.5, 0.5));
		unitWind[indexUnit]->setFlipX(true);
		this->addChild(unitWind[indexUnit]);

		auto animation = Animation::create();
		animation->setDelayPerUnit(0.3f);

		for (int i = 1; i < 19; i++) // ������ĳ�ÿ��� �̹������� ������ animation�� ���
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

		//������� ��ġ�Ͽ� �����ǵ��� ��
		testPointY[testCount] = testPointY[testCount - 1] - 80; //80��ŭ�� �Ʒ��� �������� ����
		testPointX[testCount] = 100; //ĳ����x�� 

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

		auto cache = SpriteFrameCache::getInstance(); // ������ ĳ�� ���� (�ϳ��� �����ϴ� �̱��� ��ü)
		cache->addSpriteFramesWithFile("Wood/sprite_Wood.plist"); // ������ĳ�ÿ� plist ���� �߰�
		unitWind[indexUnit] = Sprite::createWithSpriteFrameName("sprite_Wood1.png"); // ������ĳ�ÿ��� �ִϸ��̼� ���� �̹��� ����
		unitWind[indexUnit]->setPosition(Point(testPointX[testCount], testPointY[testCount]));
		unitWind[indexUnit]->setAnchorPoint(Vec2(0.5, 0.5));
		unitWind[indexUnit]->setFlipX(true);
		this->addChild(unitWind[indexUnit]);

		auto animation = Animation::create();
		animation->setDelayPerUnit(0.3f);

		for (int i = 1; i < 21; i++) // ������ĳ�ÿ��� �̹������� ������ animation�� ���
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

		//������� ��ġ�Ͽ� �����ǵ��� ��
		testPointY[testCount] = testPointY[testCount - 1] - 80; //80��ŭ�� �Ʒ��� �������� ����
		testPointX[testCount] = 100; //ĳ����x�� 

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

		auto cache = SpriteFrameCache::getInstance(); // ������ ĳ�� ���� (�ϳ��� �����ϴ� �̱��� ��ü)
		cache->addSpriteFramesWithFile("tiger/sprite_Tiger.plist"); // ������ĳ�ÿ� plist ���� �߰�
		unitWind[indexUnit] = Sprite::createWithSpriteFrameName("sprite_Tiger1.png"); // ������ĳ�ÿ��� �ִϸ��̼� ���� �̹��� ����
		unitWind[indexUnit]->setPosition(Point(testPointX[testCount], testPointY[testCount]));
		unitWind[indexUnit]->setAnchorPoint(Vec2(0.5, 0.5));
		unitWind[indexUnit]->setFlipX(true);
		this->addChild(unitWind[indexUnit]);

		auto animation = Animation::create();
		animation->setDelayPerUnit(0.3f);

		for (int i = 1; i < 23; i++) // ������ĳ�ÿ��� �̹������� ������ animation�� ���
		{
			auto frame = cache->getSpriteFrameByName(StringUtils::format("sprite_Tiger%d.png", i));
			animation->addSpriteFrame(frame);
		}

		auto animate = Animate::create(animation);
		auto action = RepeatForever::create(animate);
		unitWind[indexUnit]->runAction(action);
	}

	this->schedule(schedule_selector(InGame::tick1), 0.8f); //1�ʰ������� tick1 �۵�
}

void InGame::c_MoveToTouch()
{
	//��ġ ��ǥ �޾ƿ�
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
			this->createBullet(); //�Ѿ� ����		
		}
	}

	if (pEnemy == nullptr)
	{
		this->createEnemy(); //�� ����
	}

	//if (pEnemy2 == nullptr)
	//{
	//	this->createEnemy2(); //�� ����
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
			SimpleAudioEngine::getInstance()->preloadEffect("Item Purchase.wav"); //�޸𸮿� ȿ���� ����
			SimpleAudioEngine::getInstance()->playEffect("Item Purchase.wav", false); //ȿ�������


			pBullet[indexBullet]->removeFromParentAndCleanup(true); //�Ѿ�����
			pBullet[indexBullet] = nullptr; // �����ð� ����� ���� �� ������ ��ü������ ���� �����Ƿ� �ݵ�� nullptr�� ó���ؾ� ���� ��������..

			myCoin += 5;

			bChange = true;
		}

		//if ((Bullet_x[indexBullet] <= Enemy_x2 + 149 && Bullet_x[indexBullet] >= Enemy_x2 - 149)
		//	&& (Bullet_y[indexBullet] <= Enemy_y2 + 50 && Bullet_y[indexBullet] >= Enemy_y2 - 50))
		//{
		//	SimpleAudioEngine::getInstance()->preloadEffect("Item Purchase.wav"); //�޸𸮿� ȿ���� ����
		//	SimpleAudioEngine::getInstance()->playEffect("Item Purchase.wav", false); //ȿ�������


		//	pBullet[indexBullet]->removeFromParentAndCleanup(true); //�Ѿ�����
		//	pBullet[indexBullet] = nullptr; // �����ð� ����� ���� �� ������ ��ü������ ���� �����Ƿ� �ݵ�� nullptr�� ó���ؾ� ���� ��������..

		//	myCoin += 5;
		//	coin_label->setString(StringUtils::format("%3d", myCoin)); //���̺� ����

		//	bChange2 = true;
		//}

		if (Enemy_x <= 20 && !bChange) //���� ���� �����ϸ�
		{
			bChange = true;

			hp_count -= 1;
			Hp_label->setString(StringUtils::format("%3d", hp_count)); //���̺� ����
		}

		//if (Enemy_x2 <= 20 && !bChange2) //���� ���� �����ϸ�
		//{
		//	bChange2 = true;

		//	hp_count -= 1;
		//	Hp_label->setString(StringUtils::format("%3d", hp_count)); //���̺� ����
		//}
	}
	if (bChange)
	{
		pEnemy ->removeFromParentAndCleanup(true); //������
		pEnemy = nullptr; // �����ð� ����� ���� �� ������ ��ü������ ���� �����Ƿ� �ݵ�� nullptr�� ó���ؾ� ���� ��������..
		bChange = false;
	}

	//if (bChange2)
	//{
	//	pEnemy2->removeFromParentAndCleanup(true); //������
	//	pEnemy2 = nullptr; // �����ð� ����� ���� �� ������ ��ü������ ���� �����Ƿ� �ݵ�� nullptr�� ó���ؾ� ���� ��������..
	//	bChange2 = false;
	//}

	if (hp_count <= 0)//��������� �ѹ��� �Ǿ���ϴµ�, ������ ��
	{
		SimpleAudioEngine::getInstance()->unloadEffect("GunSound.wav"); //�޸𸮿��� ȿ���� ����
		popuplayer(this);
	}

	for (int indexBullet = 0; indexBullet <= testCount; ++indexBullet)
	{
		 if (Bullet_x[indexBullet] >= 800)
		{
			pBullet[indexBullet]->removeFromParentAndCleanup(true); //�Ѿ�����
			pBullet[indexBullet] = nullptr; // �����ð� ����� ���� �� ������ ��ü������ ���� �����Ƿ� �ݵ�� nullptr�� ó���ؾ� ���� ��������..
		}
	}


}

void InGame::popUnit(Ref* sender)
{
	SimpleAudioEngine::getInstance()->preloadEffect("Map Open.wav"); //�޸𸮿� ȿ���� ����
	SimpleAudioEngine::getInstance()->playEffect("Map Open.wav", false); //ȿ�������

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

		if (rnd[i] == 0) //0�̸�, �� �Ӽ� ����
		{
			table = "fish";
			doBuyWindUnit(table);
		}
		if (rnd[i] == 1) //1�̸�, �� �Ӽ� ����
		{
			table = "grass";
			doBuyWindUnit(table);
		}
		if (rnd[i] == 2)//2�̸�, �� �Ӽ� ����
		{
			table = "cat";
			doBuyWindUnit(table);
		}
	}
}

void InGame::popuplayer(Ref*sender)
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();

	CCDirector::sharedDirector()->pause(); //ȭ�� ����

	auto layer = GameOver::create();
	layer->setScaleX(0.8);
	layer->setScaleY(0.8);
	this->addChild(layer);
}

void InGame::popuplayer_stage(Ref*sender)
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();

	CCDirector::sharedDirector()->pause(); //ȭ�� ����

	auto layer = Stage_clear::create();
	layer->setScaleX(0.8);
	layer->setScaleY(0.8);
	this->addChild(layer);
}
