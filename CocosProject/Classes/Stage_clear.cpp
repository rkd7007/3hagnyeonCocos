#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Stage_clear.h"
#include "InGame.h"

USING_NS_CC;

//오디오 소스 관련 네임스페이스 선언 
using namespace CocosDenshion;

extern int myCoin;
extern int time_count;

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Stage_clear::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	SimpleAudioEngine::getInstance()->preloadEffect("Win.wav"); //메모리에 효과음 저장
	SimpleAudioEngine::getInstance()->playEffect("Win.wav", false); //효과음출력

	auto back_main = Sprite::create("stage_clear.png");
	back_main->setAnchorPoint(Vec2(0, 0));
	back_main->setPosition(200, -40);
	back_main->setScale(0.25f);
	this->addChild(back_main);

	auto exit = TouchBtn::create("xButton.png");
	exit->setAnchorPoint(Vec2(0, 0));
	exit->setPosition(690, 470);
	exit->setScale(0.25f);
	exit->setPriorityWithThis(true);
	this->addChild(exit);

	auto go_menu = Btn_goMenu::create("popmenuUI.png");
	go_menu->setAnchorPoint(Vec2(0, 0));
	go_menu->setPosition(380, 50);
	go_menu->setScale(0.13f);
	go_menu->setPriorityWithThis(true);
	this->addChild(go_menu);

	auto coin = Label::createWithTTF("%3d", "fonts/Maplestory Bold.ttf", 30);
	coin->setString(StringUtils::format("%3d", myCoin));
	coin->setPosition(550, 255);
	coin->setColor(Color3B::WHITE);
	this->addChild(coin);

	auto time = Label::createWithTTF("%3d", "fonts/Maplestory Bold.ttf", 30);
	time->setString(StringUtils::format("%3d", time_count));
	time->setPosition(550, 168);
	time->setColor(Color3B::WHITE);
	this->addChild(time);

	return true;
}

void Stage_clear::GoBack(Ref*sender)
{
	SimpleAudioEngine::getInstance()->unloadEffect("Win.wav");

	this->removeFromParentAndCleanup(true);
}

void Stage_clear::SceneMove(Ref*sender)
{
	//유닛 모음 창 생성
	//	auto go_menu = Label::createWithSystemFont("유닛", "DAON_2.28(L)", 20);
	//	auto go_menuitem = MenuItemLabel::create(go_menu, CC_CALLBACK_1(GameOver::SceneMove(), this));
	//	go_menuitem->setColor(Color3B(0, 0, 0));
	//	go_menuitem->setAnchorPoint(ccp(0, 0)); //중심점이 좌측 하단
	//	go_menuitem->setPosition(Point(380, 50));
	//
	//	auto menu = Menu::create(go_menu, NULL);
	//	this->addChild(menu);
	//	Director::getInstance()->replaceScene(StageScene::createScene());
}