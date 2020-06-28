#include "StageScene.h"
#include "SimpleAudioEngine.h"
#include "InGame.h"

USING_NS_CC;

//����� �ҽ� ���� ���ӽ����̽� ����
using namespace CocosDenshion;

Scene* StageScene::createScene()
{
	return StageScene::create();
}

// on "init" you need to initialize your instance
bool StageScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	SimpleAudioEngine::getInstance()->playBackgroundMusic("MainSound.mp3", true); //�ݺ��ؼ� ���

	auto listener = EventListenerTouchOneByOne::create(); //�̺�Ʈ ������ ����
	listener->setSwallowTouches(true);

	//���
	auto back_main = Sprite::create("stageMap.png");
	back_main->setAnchorPoint(Vec2(0, 0));
	back_main->setPosition(0, 0);
	this->addChild(back_main);

	//�������� 1 png
	auto stage1 = Sprite::create("stageUI1.png");
	stage1->setAnchorPoint(Vec2(0, 0));
	stage1->setPosition(Vec2(120, 200));
	stage1->setScale(0.3);
	this->addChild(stage1);

	//�������� 2 png
	auto stage2 = Sprite::create("stageUI2.png");
	stage2->setAnchorPoint(Vec2(0, 0));
	stage2->setPosition(Vec2(400, 200));
	stage2->setScale(0.3);
	this->addChild(stage2);

	//�������� 3 png
	auto stage3 = Sprite::create("stageUI3.png");
	stage3->setAnchorPoint(Vec2(0, 0));
	stage3->setPosition(Vec2(680, 200));
	stage3->setScale(0.3);
	this->addChild(stage3);

	//�������� 1 ���̺�
	auto goStage1 = Label::createWithTTF("1", "fonts/Maplestory Light.ttf", 50);
	auto stage_ui1 = MenuItemLabel::create(goStage1, CC_CALLBACK_1(StageScene::PlayStage1, this));
	stage_ui1->setColor(Color3B(255, 255, 255));
	stage_ui1->setPosition(Vec2(-280, 0));

	//�������� 2 ���̺�
	auto goStage2 = Label::createWithTTF("2", "fonts/Maplestory Light.ttf", 50);
	auto stage_ui2 = MenuItemLabel::create(goStage2, CC_CALLBACK_1(StageScene::PlayStage2, this));
	stage_ui2->setColor(Color3B(255, 255, 255));
	stage_ui2->setPosition(Vec2(0, 0));

	//�������� 3 ���̺�
	auto goStage3 = Label::createWithTTF("3", "fonts/Maplestory Light.ttf", 50);
	auto stage_ui3 = MenuItemLabel::create(goStage3, CC_CALLBACK_1(StageScene::PlayStage3, this));
	stage_ui3->setColor(Color3B(255, 255, 255));
	stage_ui3->setPosition(Vec2(280, 0));

	auto menu = Menu::create(stage_ui1, stage_ui2, stage_ui3, NULL);
	this->addChild(menu);

	return true;
}

void StageScene::PlayStage1(Ref* sender)
{
	//�������� 1
	Director::getInstance()->replaceScene(InGame::createScene());
}

void StageScene::PlayStage2(Ref* sender)
{
	//�������� 2
	Director::getInstance()->replaceScene(InGame::createScene());
}

void StageScene::PlayStage3(Ref* sender)
{
	//�������� 3
	Director::getInstance()->replaceScene(InGame::createScene());
}

