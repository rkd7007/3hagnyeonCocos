#include "StageScene.h"
#include "SimpleAudioEngine.h"
#include "InGame.h"
#include "Option.h"

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
	auto stage1 = MenuItemImage::create("stageUI1.png", "", CC_CALLBACK_1(StageScene::PlayStage1, this));
	stage1->setAnchorPoint(Vec2(0, 0));
	stage1->setPosition(Vec2(140, 200));
	stage1->setScale(0.22);

	//�������� 2 png
	auto stage2 = MenuItemImage::create("stageUI2.png", "", CC_CALLBACK_1(StageScene::PlayStage2, this));
	stage2->setAnchorPoint(Vec2(0, 0));
	stage2->setPosition(Vec2(420, 200));
	stage2->setScale(0.22);

	//�������� 3 png
	auto stage3 = MenuItemImage::create("stageUI3.png", "", CC_CALLBACK_1(StageScene::PlayStage3, this));
	stage3->setAnchorPoint(Vec2(0, 0));
	stage3->setPosition(Vec2(700, 200));
	stage3->setScale(0.22);

	//���� ��� �ɼ�
	auto option = MenuItemImage::create("howPlayUI.png", "", CC_CALLBACK_1(StageScene::popupOption, this));
	option->setAnchorPoint(Vec2(0, 0));
	option->setPosition(Vec2(870, 20));
	option->setScale(0.25);

	auto menu = Menu::create(stage1, stage2, stage3, option, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

	return true;
}

void StageScene::PlayStage1(Ref* sender)
{
	//�������� 1
	//Director::getInstance()->replaceScene(InGame::createScene());
	auto Scene = TransitionCrossFade::create(0.3f, InGame::createScene());
	Director::getInstance()->pushScene(Scene);
}

void StageScene::PlayStage2(Ref* sender)
{
	//�������� 2
	//Director::getInstance()->replaceScene(InGame::createScene());
	auto Scene = TransitionCrossFade::create(0.3f, InGame::createScene());
	Director::getInstance()->pushScene(Scene);
}

void StageScene::PlayStage3(Ref* sender)
{
	//�������� 3
	//Director::getInstance()->replaceScene(InGame::createScene());
	auto Scene = TransitionCrossFade::create(0.3f, InGame::createScene());
	Director::getInstance()->pushScene(Scene);
}

void StageScene::popupOption(Ref*sender)
{
	auto layer = Option::create();
	layer->setScaleX(0.8);
	layer->setScaleY(0.8);
	this->addChild(layer);
}