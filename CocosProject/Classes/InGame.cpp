#include "InGame.h"
#include "SimpleAudioEngine.h"
#include "CreatePopUnit.h"
#include "CreatePopUnitMix.h"
#include "GameOver.h"
#include "PopAllUnit.h"

using namespace cocos2d;

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
	auto label_chose_unit = Label::createWithSystemFont("���� ����", "DAON_2.28(L)", 20);
	auto Unititem = MenuItemLabel::create(label_chose_unit, CC_CALLBACK_1(InGame::popUnit, this));
	Unititem->setColor(Color3B(0, 0, 0));
	Unititem->setAnchorPoint(ccp(1, 1)); //�߽����� ���� ���
	Unititem->setPosition(Point(winSize.width - 500, winSize.height - 300));

	//���� �Ӽ� �����ϴ� �˾� â ����
	auto label_Mix_unit = Label::createWithSystemFont("���� ����", "DAON_2.28(L)", 20);
	auto UnitMixitem = MenuItemLabel::create(label_Mix_unit, CC_CALLBACK_1(InGame::popUnitMix, this));
	UnitMixitem->setColor(Color3B(0, 0, 0));
	UnitMixitem->setAnchorPoint(ccp(1, 1)); //�߽����� ���� ���
	UnitMixitem->setPosition(Point(winSize.width - 600, winSize.height - 300));

	//���� ���� â ����
	auto label_All_unit = Label::createWithSystemFont("����", "DAON_2.28(L)", 20);
	auto UnitAllitem = MenuItemLabel::create(label_All_unit, CC_CALLBACK_1(InGame::popUnitAll, this));
	UnitAllitem->setColor(Color3B(0, 0, 0));
	UnitAllitem->setAnchorPoint(ccp(0, 0)); //�߽����� ���� �ϴ�
	UnitAllitem->setPosition(Point(200, winSize.height - 800));

	auto menu = Menu::create(Unititem, UnitMixitem, UnitAllitem, NULL);
	//menu->setAnchorPoint(ccp(1, 1)); //�߽����� ���� ���
	//menu->setPosition(Point(winSize.width - 100, winSize.height - 50));
	//menu->alignItemsHorizontally(); //�¿캴��
	this->addChild(menu);

	createUnit(); //�ʱ� ���� ĳ���� ������ ����

	this->schedule(schedule_selector(InGame::timer), 1.0f); //1�ʰ������� tick1 �۵�

	return true;
}

void InGame::BaseFunc()
{
	//���� �ʱ�ȭ
	time_count = 60; //�ð�
	E_time = 50;
	B_time = 50;
	c_Xpoint = 300;
	c_Ypoint = 300;
	score = 0; //����
	testPointX[0] = 100;
	testPointY[0] = 380;

	//���
	auto back_main = Sprite::create("back_main.png");
	back_main->setAnchorPoint(Vec2(0, 0));
	back_main->setPosition(0, 0);
	this->addChild(back_main);

	//Ÿ�̸�
	timer_label = Label::createWithSystemFont("Time : ", "DAON_2.28(L)", 30);
	timer_label->setPosition(90, 510);
	timer_label->setColor(Color3B::BLACK);
	this->addChild(timer_label);

	//���̺� ����
	timer_label->setString(StringUtils::format("Time : %3d", time_count));

	//����
	score_label = Label::createWithSystemFont("Score : ", "DAON_2.28(L)", 30);
	score_label->setPosition(Vec2(270, 510));
	score_label->setColor(Color3B::BLACK);
	this->addChild(score_label);

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
	timer_label->setString(StringUtils::format("Time : %3d", time_count)); //���̺� ����

	if (time_count == -1) //0�� ���̰� 1���� ��������
	{
		//���� ����
		SimpleAudioEngine::getInstance()->unloadEffect("GunSound.wav"); //�޸𸮿��� ȿ���� ����
		Director::getInstance()->replaceScene(GameOver::createScene()); //���ӿ��� ������ �̵�
	}
}


void InGame::timer_for_monsterOut(float f)
{
	//���� ����
	SimpleAudioEngine::getInstance()->unloadEffect("GunSound.wav"); //�޸𸮿��� ȿ���� ����
	Director::getInstance()->replaceScene(GameOver::createScene()); //���ӿ��� ������ �̵�

}



void InGame::createBullet()
{
	indexBullet += 1;

	SimpleAudioEngine::getInstance()->preloadEffect("GunSound.wav"); //�޸𸮿� ȿ���� ����
	SimpleAudioEngine::getInstance()->playEffect("GunSound.wav", false); //ȿ�������

	pBullet[indexBullet] = Sprite::create("ball.png");
	pBullet[indexBullet]->setPosition(Vec2(testPointX[testCount] - 50, testPointY[testCount]));

	this->addChild(pBullet[indexBullet]);

	//auto SmokeParticle = ParticleSmoke::create();
	//SmokeParticle->setDuration(0.1f); //��� �ð�
	//SmokeParticle->setSpeed(100); //���� �ð�
	//SmokeParticle->setGravity(Point(0, 300)); //y������ �߷��� 300���� ����
	//SmokeParticle->setAutoRemoveOnFinish(true); //��ƼŬ ���ӽð� ���� �� �ڵ�����
	//SmokeParticle->setPosition(Vec2(pBullet[indexBullet]->getPositionX(), pBullet[indexBullet]->getPositionY()));
	//this->addChild(SmokeParticle);

	auto myActionForward = MoveTo::create(1, Vec2(-10, testPointY[testCount])); //�������� ������
	auto myAction = Sequence::create(Place::create(Vec2(testPointX[testCount] - 50, testPointY[testCount])), myActionForward, nullptr); //���� ��ġ�� �ٲٱ�
	pBullet[indexBullet]->runAction(myAction);
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

	auto action1 = MoveTo::create(3, Vec2(70, 50));//�Ʒ�
	auto action2 = MoveTo::create(5, Vec2(900, 50));//������
	auto action3 = MoveTo::create(3, Vec2(900, 450));//��
	auto action4 = MoveTo::create(5, Vec2(70, 450));//����
	auto action5 = Sequence::create(action1, action2, action3, action4, NULL);
	auto action6 = RepeatForever::create(action5); //��� �ݺ���Ŵ
	pEnemy->runAction(action6);

	count_enemy += 1; //�� �� ����
	log("���� �� : %d", count_enemy);

	//���� 100������ �Ѿ��
	if (count_enemy >= 100)
		MaxEnemy = true;
}

void InGame::doBuyWindUnit(std::string tableName)
{
	if (tableName == "wind")
	{
		log("wind ȣ��");
	}
	if (tableName == "ground")
	{
		log("ground ȣ��");
		log("x��ġ : %d, y��ġ : %d", testPointX[testCount], testPointY[testCount]);

		indexUnit += 1;
		testCount += 1;

		//������� ��ġ�Ͽ� �����ǵ��� ��
		testPointY[testCount] = testPointY[testCount - 1] - 80;
		testPointX[testCount] = 100;

		if (testPointY[testCount] <= 100)
		{
			testPointY[testCount] = 380;
			testPointX[testCount] += 80;
		}

		auto cache = SpriteFrameCache::getInstance(); // ������ ĳ�� ���� (�ϳ��� �����ϴ� �̱��� ��ü)
		cache->addSpriteFramesWithFile("ground_Gun.plist"); // ������ĳ�ÿ� plist ���� �߰�
		unitWind[indexUnit] = Sprite::createWithSpriteFrameName("ground_Gun1.png"); // ������ĳ�ÿ��� �ִϸ��̼� ���� �̹��� ����
		unitWind[indexUnit]->setPosition(Point(testPointX[testCount], testPointY[testCount]));
		unitWind[indexUnit]->setAnchorPoint(Vec2(0.5, 0.5));
		unitWind[indexUnit]->setFlipX(true);
		this->addChild(unitWind[indexUnit]);

		auto animation = Animation::create();
		animation->setDelayPerUnit(0.3f);

		for (int i = 1; i < 6; i++) // ������ĳ�ÿ��� �̹������� ������ animation�� ���
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
		log("fire ȣ��");
	}

	this->schedule(schedule_selector(InGame::tick1), 0.8f); //1�ʰ������� tick1 �۵�
}

void InGame::c_MoveToTouch()
{
	//��ġ ��ǥ �޾ƿ�
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(InGame::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//if (isTouch) //&& isCreatePly
	//{
	//	//��ġ ��ġ�� �ű�� - �ڿ������� ����
	//	//c_Xpoint = isTouchpointX;
	//	//c_Ypoint = isTouchpointY;
	//	//pPlayer->setPosition(Vec2(c_Xpoint, c_Ypoint));
	//	//isTouch = false;

	//	//��ġ ��ġ�� �����̱� - ������ ����
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
		this->createBullet(); //�Ѿ� ����		
	}

	if (pEnemy == nullptr)
	{
		this->createEnemy(); //�� ����
	}

	Bullet_x = pBullet[indexBullet]->getPosition().x;
	Bullet_y = pBullet[indexBullet]->getPosition().y;

	Enemy_x = pEnemy->getPosition().x;
	Enemy_y = pEnemy->getPosition().y;

	//if (pBullet->getBoundingBox().intersectsRect(pEnemy->getBoundingBox()))//�浹�ϸ�
	if((Bullet_x <= Enemy_x +149 && Bullet_x >= Enemy_x - 149) && (Bullet_y <= Enemy_y + 50 && Bullet_y >= Enemy_y - 50))
	{
		pBullet[indexBullet]->removeFromParentAndCleanup(true); //�Ѿ�����
		pBullet[indexBullet] = nullptr; // �����ð� ����� ���� �� ������ ��ü������ ���� �����Ƿ� �ݵ�� nullptr�� ó���ؾ� ���� ��������..

		score = score + 10;
		score_label->setString(StringUtils::format("Score : %3d", score)); //���̺� ����

		bChange = true;

		/*int killenemy = UserDefault::getInstance()->getIntegerForKey("KILLENEMY") + 1;
		UserDefault::getInstance()->setIntegerForKey("KILLENEMY", killenemy);
		UserDefault::getInstance()->flush();
		killenemy_label->setString(StringUtils::format("KILL : %3d", killenemy));*/

		//auto particle = ParticleGalaxy::create();
		//particle->setDuration(0.2f); //��� �ð�
		//particle->setSpeed(100); //���� �ð�
		//particle->setGravity(Point(0, 300)); //y������ �߷��� 300���� ����
		//particle->setAutoRemoveOnFinish(true); //��ƼŬ ���ӽð� ���� �� �ڵ�����
		//particle->setPosition(Vec2(pEnemy->getPositionX(), pEnemy->getPositionY()));
		//this->addChild(particle);
	}

	if (bChange)
	{
		pEnemy->removeFromParentAndCleanup(true); //������
		pEnemy = nullptr; // �����ð� ����� ���� �� ������ ��ü������ ���� �����Ƿ� �ݵ�� nullptr�� ó���ؾ� ���� ��������..

		bChange = false;
	}
	else if (Bullet_x <= -1)
	{
		pBullet[indexBullet]->removeFromParentAndCleanup(true); //�Ѿ�����
		pBullet[indexBullet] = nullptr; // �����ð� ����� ���� �� ������ ��ü������ ���� �����Ƿ� �ݵ�� nullptr�� ó���ؾ� ���� ��������..
	}
}

void InGame::popUnit(Ref* sender)
{
	CreatePopUnit* popup = CreatePopUnit::create();
	this->addChild(popup, 10);

	//auto layer = CreatePopUnit::create(); //���̾� ����
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
	int rnd[3] = { 1,1,1 }; //�׽�Ʈ��

	//for (int i = 0; i < 3; i++)
	//	rnd[i] = rand() % 3; //0~2

	for (int i = 0; i < 3; i++)
	{
		log("rand num : %d", rnd[i]);

		if (rnd[i] == 0) //0�̸�, �ٶ� �Ӽ� ����
		{
			if (i == 0) //ù��° �����̸�
			{
				testPointX[testCount] = 100;
				testPointY[testCount] = 380;
			}
			if (i == 1) //�ι�° �����̸�
			{
				testPointX[testCount] = 100;
				testPointY[testCount] = 300;
			}
			if (i == 2) //����° �����̸�
			{
				testPointX[testCount] = 100;
				testPointY[testCount] = 220;
			}
			table = "wind";
			doBuyWindUnit(table);
		}
		if (rnd[i] == 1) //1�̸�, �� �Ӽ� ����
		{
			//���� ���� �׸� ��ǥ = �ִ� : x 100, y 400, �ּ� : x 100, y 100
			//���ְ��� ���� = x 80, y 80

			//if (i == 0) //ù��° �����̸�
			//{
			//	testPointX[testCount] = 100;
			//	testPointY[testCount] = 380;
			//}
			//if (i == 1) //�ι�° �����̸�
			//{
			//	testPointX[testCount+1] = 100;
			//	testPointY[testCount+1] = 300;
			//}
			//if (i == 2) //����° �����̸�
			//{
			//	testPointX[testCount+2] = 100;
			//	testPointY[testCount+2] = 220;
			//}
			table = "ground";
			doBuyWindUnit(table);
		}
		if (rnd[i] == 2)//2�̸�, �� �Ӽ� ����
		{
			if (i == 0) //ù��° �����̸�
			{
				testPointX[testCount] = 100;
				testPointY[testCount] = 380;
			}
			if (i == 1) //�ι�° �����̸�
			{
				testPointX[testCount] = 100;
				testPointY[testCount] = 300;
			}
			if (i == 2) //����° �����̸�
			{
				testPointX[testCount] = 100;
				testPointY[testCount] = 220;
			}
			table = "fire";
			doBuyWindUnit(table);
		}
	}
}