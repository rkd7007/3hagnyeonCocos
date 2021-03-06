#include "StageScene.h"
#include "SimpleAudioEngine.h"
#include "InGame.h"
#include "Option.h"

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
	auto stage1 = MenuItemImage::create("stageUI1.png", "stageUI1_click.png", CC_CALLBACK_1(StageScene::PlayStage1, this));
	stage1->setAnchorPoint(Vec2(0, 0));
	stage1->setPosition(Vec2(140, 200));
	stage1->setScale(0.22);

	//스테이지 2 png
	auto stage2 = MenuItemImage::create("stageUI2.png", "stageUI2_click.png", CC_CALLBACK_1(StageScene::PlayStage2, this));
	stage2->setAnchorPoint(Vec2(0, 0));
	stage2->setPosition(Vec2(420, 200));
	stage2->setScale(0.22);

	//스테이지 3 png
	auto stage3 = MenuItemImage::create("stageUI3.png", "stageUI3_click.png", CC_CALLBACK_1(StageScene::PlayStage3, this));
	stage3->setAnchorPoint(Vec2(0, 0));
	stage3->setPosition(Vec2(700, 200));
	stage3->setScale(0.22);

	//게임 방법 옵션
	auto option = MenuItemImage::create("howPlayUI.png", "howPlayUI_click.png", CC_CALLBACK_1(StageScene::popupOption, this));
	option->setAnchorPoint(Vec2(0, 0));
	option->setPosition(Vec2(870, 20));
	option->setScale(0.25);

	auto handicap = MenuItemImage::create("handicp.png", "howPlayUI_click.png", CC_CALLBACK_1(StageScene::popupOption, this));
	handicap->setAnchorPoint(Vec2(0, 0));
	handicap->setPosition(Vec2(870, 85));
	handicap->setScale(0.3);

	auto select = MenuItemImage::create("stageSelect.png", "howPlayUI_click.png", CC_CALLBACK_1(StageScene::popupOption, this));
	select->setAnchorPoint(Vec2(0, 0));
	select->setPosition(Vec2(130, 430));
	select->setScale(0.75);

	auto menu = Menu::create(stage1, stage2, stage3, option, handicap, select, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

	return true;
}

void StageScene::PlayStage1(Ref* sender)
{
	//스테이지 1
	auto Scene = TransitionCrossFade::create(0.3f, InGame::createScene());
	Director::getInstance()->pushScene(Scene);
}

void StageScene::PlayStage2(Ref* sender)
{
	//스테이지 2
	auto Scene = TransitionCrossFade::create(0.3f, InGame::createScene());
	Director::getInstance()->pushScene(Scene);
}

void StageScene::PlayStage3(Ref* sender)
{
	//스테이지 3
	auto Scene = TransitionCrossFade::create(0.3f, InGame::createScene());
	Director::getInstance()->pushScene(Scene);
}

void StageScene::popupOption(Ref*sender)
{
	SimpleAudioEngine::getInstance()->preloadEffect("Map Open.wav"); //메모리에 효과음 저장
	SimpleAudioEngine::getInstance()->playEffect("Map Open.wav", false); //효과음출력

	auto layer = Option::create();
	layer->setScaleX(0.8);
	layer->setScaleY(0.8);
	this->addChild(layer);

	SimpleAudioEngine::getInstance()->unloadEffect("Map Open.wav");
}