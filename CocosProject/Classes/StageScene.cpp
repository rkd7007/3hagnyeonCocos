#include "StageScene.h"
#include "SimpleAudioEngine.h"
#include "InGame.h"

USING_NS_CC;

//오디오 소스 관련 네임스페이스 선언
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

	SimpleAudioEngine::getInstance()->playBackgroundMusic("MainSound.mp3", true); //반복해서 출력

	auto listener = EventListenerTouchOneByOne::create(); //이벤트 리스너 생성
	listener->setSwallowTouches(true);

	//배경
	auto back_main = Sprite::create("test.png");
	back_main->setAnchorPoint(Vec2(0, 0));
	back_main->setPosition(0, 0);
	this->addChild(back_main);

	//스테이지 1 png
	auto stage1 = MenuItemImage::create("stageUI1.png", "", CC_CALLBACK_1(StageScene::PlayStage1, this));
	stage1->setAnchorPoint(Vec2(0, 0));
	stage1->setPosition(Vec2(120, 200));
	stage1->setScale(0.2);

	//스테이지 2 png
	auto stage2 = MenuItemImage::create("stageUI2.png", "", CC_CALLBACK_1(StageScene::PlayStage2, this));
	stage2->setAnchorPoint(Vec2(0, 0));
	stage2->setPosition(Vec2(400, 200));
	stage2->setScale(0.2);

	//스테이지 3 png
	auto stage3 = MenuItemImage::create("stageUI3.png", "", CC_CALLBACK_1(StageScene::PlayStage3, this));
	stage3->setAnchorPoint(Vec2(0, 0));
	stage3->setPosition(Vec2(680, 200));
	stage3->setScale(0.2);

	auto menu = Menu::create(stage1, stage2, stage3, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

	return true;
}

void StageScene::PlayStage1(Ref* sender)
{
	//스테이지 1
	//Director::getInstance()->replaceScene(InGame::createScene());
	auto Scene = TransitionCrossFade::create(0.3f, InGame::createScene());
	Director::getInstance()->pushScene(Scene);
}

void StageScene::PlayStage2(Ref* sender)
{
	//스테이지 2
	//Director::getInstance()->replaceScene(InGame::createScene());
	auto Scene = TransitionCrossFade::create(0.3f, InGame::createScene());
	Director::getInstance()->pushScene(Scene);
}

void StageScene::PlayStage3(Ref* sender)
{
	//스테이지 3
	//Director::getInstance()->replaceScene(InGame::createScene());
	auto Scene = TransitionCrossFade::create(0.3f, InGame::createScene());
	Director::getInstance()->pushScene(Scene);
}

