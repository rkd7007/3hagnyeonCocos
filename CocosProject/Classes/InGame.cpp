#include "InGame.h"
#include "SimpleAudioEngine.h"
#include "CreatePopUnit.h"

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

	SimpleAudioEngine::getInstance()->playBackgroundMusic("CasualGameBGM.mp3", true); //�ݺ��ؼ� ���

	BaseFunc();
	this->scheduleUpdate();

	/*
	//�ٶ��Ӽ����ֱ��� �޴�
	auto label_Unit_wind = Label::createWithSystemFont("�ٶ� �Ӽ�", "DAON_2.28(L)", 30);
	auto Unititem1 = MenuItemLabel::create(label_Unit_wind, CC_CALLBACK_1(InGame::doBuyWindUnit, this));
	Unititem1->setColor(Color3B(0, 0, 0));
	Unititem1->setAnchorPoint(Vec2(0.5, 0.5)); 
	Unititem1->setPosition(Vec2(100, 240)); 


	//���Ӽ����ֱ��� �޴�
	auto label_Unit_ground = Label::createWithSystemFont("�� �Ӽ�", "DAON_2.28(L)", 30);
	auto Unititem2 = MenuItemLabel::create(label_Unit_ground, CC_CALLBACK_1(InGame::doBuyWindUnit, this));
	Unititem2->setColor(Color3B(0, 0, 0));
	Unititem2->setAnchorPoint(Vec2(0.5, 0.5)); 
	Unititem2->setPosition(Vec2(260, 240)); 


	//���Ӽ����ֱ��� �޴�
	auto label_Unit_water = Label::createWithSystemFont("�� �Ӽ�", "DAON_2.28(L)", 30);
	auto Unititem3 = MenuItemLabel::create(label_Unit_water, CC_CALLBACK_1(InGame::doBuyWindUnit, this));
	Unititem3->setColor(Color3B(0, 0, 0));
	Unititem3->setAnchorPoint(Vec2(0.5, 0.5));
	Unititem3->setPosition(Vec2(400, 240));

	auto menu = Menu::create(Unititem1, Unititem2, Unititem3, NULL);
	this->addChild(menu);
	*/
	
	//���� �Ӽ� �̴� �˾� â ����
	auto label_chose_unit = Label::createWithSystemFont("menu", "DAON_2.28(L)", 30);
	auto Unititem = MenuItemLabel::create(label_chose_unit, CC_CALLBACK_1(InGame::poplayer, this));
	Unititem->setColor(Color3B(0, 0, 0));
	Unititem->setAnchorPoint(Vec2(0.5, 0.5));
	Unititem->setPosition(Vec2(400, 240));

	auto menu = Menu::create(Unititem, NULL);
	this->addChild(menu);

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
	isTouch = false;

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
	timer_label->setString(StringUtils::format("Time : %3d", time_count)); //���̺� ����

	if (time_count == -1) //0�� ���̰� 1���� ��������
	{
		//���� ���� ȭ�� ������ ����...
		/*auto layer = GameLayer::create();
		layer->setScaleX(0.8);
		layer->setScaleY(0.8);
		this->addChild(layer);*/

		SimpleAudioEngine::getInstance()->unloadEffect("GunSound.wav"); //�޸𸮿��� ȿ���� ����
		//exit(0);
	}
}

void InGame::createBullet()
{
	SimpleAudioEngine::getInstance()->preloadEffect("GunSound.wav"); //�޸𸮿� ȿ���� ����
	SimpleAudioEngine::getInstance()->playEffect("GunSound.wav", false); //ȿ�������

	pBullet = Sprite::create("ball.png");
	pBullet->setPosition(Vec2(c_Xpoint - 50, c_Ypoint));

	this->addChild(pBullet);

	auto SmokeParticle = ParticleSmoke::create();
	SmokeParticle->setDuration(0.1f); //��� �ð�
	SmokeParticle->setSpeed(100); //���� �ð�
	SmokeParticle->setGravity(Point(0, 300)); //y������ �߷��� 300���� ����
	SmokeParticle->setAutoRemoveOnFinish(true); //��ƼŬ ���ӽð� ���� �� �ڵ�����
	SmokeParticle->setPosition(Vec2(pBullet->getPositionX(), pBullet->getPositionY()));
	this->addChild(SmokeParticle);

	auto myActionForward = MoveTo::create(1, Vec2(-10, c_Ypoint)); //�������� ������
	auto myAction = Sequence::create(Place::create(Vec2(c_Xpoint - 50, c_Ypoint)), myActionForward, nullptr); //���� ��ġ�� �ٲٱ�
	pBullet->runAction(myAction);
}


bool InGame::onTouchBegan(Touch* touch, Event* event)
{
	auto touchpoint = touch->getLocation(); //��ġ��ġ�˾ƿ���
	isTouchpointX = touchpoint.x; //��ġ x��ǥ �޾ƿ�
	isTouchpointY = touchpoint.y; //��ġ y��ǥ �޾ƿ�
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

	auto action1 = MoveTo::create(3, Vec2(70, 50));//�Ʒ�
	auto action2 = MoveTo::create(5, Vec2(900, 50));//������
	auto action3 = MoveTo::create(3, Vec2(900, 450));//��
	auto action4 = MoveTo::create(5, Vec2(70, 450));//����
	auto action5 = Sequence::create(action1, action2, action3, action4, NULL);
	auto action6 = RepeatForever::create(action5); //��� �ݺ���Ŵ
	pEnemy->runAction(action6);
}

void InGame::doBuyWindUnit(Ref*pSender)
{
	//���̺��� ���� ���� �ٶ� �Ӽ��̸�
	auto test = Label::create();

	//���̺��� ���� ���� �� �Ӽ��̸�


	//���̺��� ���� ���� �� �Ӽ��̸�

	auto cache = SpriteFrameCache::getInstance(); // ������ ĳ�� ���� (�ϳ��� �����ϴ� �̱��� ��ü)
	cache->addSpriteFramesWithFile("ground_Gun.plist"); // ������ĳ�ÿ� plist ���� �߰�
	unitWind1 = Sprite::createWithSpriteFrameName("ground_Gun1.png"); // ������ĳ�ÿ��� �ִϸ��̼� ���� �̹��� ����

	unitWind1->setPosition(Point(500, 500));
	unitWind1->setAnchorPoint(Vec2(0.5, 0.5));
	this->addChild(unitWind1);

	auto animation = Animation::create();
	animation->setDelayPerUnit(0.3f);

	for (int i = 1; i < 6; i++) // ������ĳ�ÿ��� �̹������� ������ animation�� ���
	{
		auto frame = cache->getSpriteFrameByName(StringUtils::format("ground_Gun%d.png", i));
		animation->addSpriteFrame(frame);
	}

	auto animate = Animate::create(animation);
	auto action = RepeatForever::create(animate);
	unitWind1->runAction(action);

	this->schedule(schedule_selector(InGame::tick1), 0.8f); //1�ʰ������� tick1 �۵�
}

void InGame::c_MoveToTouch()
{
	//��ġ ��ǥ �޾ƿ�
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(InGame::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	if (isTouch) //&& isCreatePly
	{
		//��ġ ��ġ�� �ű�� - �ڿ������� ����
		//c_Xpoint = isTouchpointX;
		//c_Ypoint = isTouchpointY;
		//pPlayer->setPosition(Vec2(c_Xpoint, c_Ypoint));
		//isTouch = false;

		//��ġ ��ġ�� �����̱� - ������ ����
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
		this->createBullet(); //�Ѿ� ����		
	}

	if (pEnemy == nullptr)
	{
		this->createEnemy(); //�� ����
	}

	Bullet_x = pBullet->getPosition().x;
	Bullet_y = pBullet->getPosition().y;

	Enemy_x = pEnemy->getPosition().x;
	Enemy_y = pEnemy->getPosition().y;

	//if (pBullet->getBoundingBox().intersectsRect(pEnemy->getBoundingBox()))//�浹�ϸ�
	if((Bullet_x <= Enemy_x +149 && Bullet_x >= Enemy_x - 149) && (Bullet_y <= Enemy_y + 50 && Bullet_y >= Enemy_y - 50))
	{
		pBullet->removeFromParentAndCleanup(true); //�Ѿ�����
		pBullet = nullptr; // �����ð� ����� ���� �� ������ ��ü������ ���� �����Ƿ� �ݵ�� nullptr�� ó���ؾ� ���� ��������..

		score = score + 10;
		score_label->setString(StringUtils::format("Score : %3d", score)); //���̺� ����

		bChange = true;

		/*int killenemy = UserDefault::getInstance()->getIntegerForKey("KILLENEMY") + 1;
		UserDefault::getInstance()->setIntegerForKey("KILLENEMY", killenemy);
		UserDefault::getInstance()->flush();

		killenemy_label->setString(StringUtils::format("KILL : %3d", killenemy));*/

		auto particle = ParticleGalaxy::create();
		particle->setDuration(0.2f); //��� �ð�
		particle->setSpeed(100); //���� �ð�
		particle->setGravity(Point(0, 300)); //y������ �߷��� 300���� ����
		particle->setAutoRemoveOnFinish(true); //��ƼŬ ���ӽð� ���� �� �ڵ�����
		particle->setPosition(Vec2(pEnemy->getPositionX(), pEnemy->getPositionY()));
		this->addChild(particle);
	}

	if (bChange)
	{
		pEnemy->removeFromParentAndCleanup(true); //�Ѿ�����
		pEnemy = nullptr; // �����ð� ����� ���� �� ������ ��ü������ ���� �����Ƿ� �ݵ�� nullptr�� ó���ؾ� ���� ��������..

		bChange = false;
	}

	else if (Bullet_x <= -1)
	{
		pBullet->removeFromParentAndCleanup(true); //�Ѿ�����
		pBullet = nullptr; // �����ð� ����� ���� �� ������ ��ü������ ���� �����Ƿ� �ݵ�� nullptr�� ó���ؾ� ���� ��������..
	}
}

void InGame::poplayer(Ref* sender)
{
	auto layer = CreatePopUnit::create(); //���̾� ����
	layer->setScaleX(0.5);
	layer->setScaleY(0.5);
	this->addChild(layer);
}

void InGame::createPlayer()
{

}