#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Stage_clear.h"
#include "InGame.h"

USING_NS_CC;

//오디오 소스 관련 네임스페이스 선언 
using namespace CocosDenshion;


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

	//auto parent = (InGame *)this->getParent();
	//parent->time_count;
	//parent->timer_label;

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

	//timer_label->setPosition(380, 100);
	//timer_label->setString(StringUtils::format("Time : %3d", parent->time_count));


	return true;
}



void Stage_clear::GoBack(Ref*sender)
{
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