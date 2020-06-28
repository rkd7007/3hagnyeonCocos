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
	auto back_main = Sprite::create("stageMap.png");
	back_main->setAnchorPoint(Vec2(0, 0));
	back_main->setPosition(0, 0);
	this->addChild(back_main);

	//스테이지 1 png
	auto stage1 = Sprite::create("stageUI1.png");
	stage1->setAnchorPoint(Vec2(0, 0));
	stage1->setPosition(Vec2(120, 200));
	stage1->setScale(0.3);
	this->addChild(stage1);

	//스테이지 2 png
	auto stage2 = Sprite::create("stageUI2.png");
	stage2->setAnchorPoint(Vec2(0, 0));
	stage2->setPosition(Vec2(400, 200));
	stage2->setScale(0.3);
	this->addChild(stage2);

	//스테이지 3 png
	auto stage3 = Sprite::create("stageUI3.png");
	stage3->setAnchorPoint(Vec2(0, 0));
	stage3->setPosition(Vec2(680, 200));
	stage3->setScale(0.3);
	this->addChild(stage3);

	//스테이지 1 레이블
	auto goStage1 = Label::createWithTTF("1", "fonts/Maplestory Light.ttf", 50);
	auto stage_ui1 = MenuItemLabel::create(goStage1, CC_CALLBACK_1(StageScene::PlayStage1, this));
	stage_ui1->setColor(Color3B(255, 255, 255));
	stage_ui1->setPosition(Vec2(-280, 0));

	//스테이지 2 레이블
	auto goStage2 = Label::createWithTTF("2", "fonts/Maplestory Light.ttf", 50);
	auto stage_ui2 = MenuItemLabel::create(goStage2, CC_CALLBACK_1(StageScene::PlayStage2, this));
	stage_ui2->setColor(Color3B(255, 255, 255));
	stage_ui2->setPosition(Vec2(0, 0));

	//스테이지 3 레이블
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
	//스테이지 1
	Director::getInstance()->replaceScene(InGame::createScene());
}

void StageScene::PlayStage2(Ref* sender)
{
	//스테이지 2
	Director::getInstance()->replaceScene(InGame::createScene());
}

void StageScene::PlayStage3(Ref* sender)
{
	//스테이지 3
	Director::getInstance()->replaceScene(InGame::createScene());
}

