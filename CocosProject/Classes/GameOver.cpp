#include "GameOver.h"
#include "SimpleAudioEngine.h"
#include "InGame.h"
#include "HelloWorldScene.h"

USING_NS_CC;

//오디오 소스 관련 네임스페이스 선언
using namespace CocosDenshion;

Scene* GameOver::createScene()
{
	return GameOver::create();
}

// on "init" you need to initialize your instance
bool GameOver::init()
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
	createBackground();

	//메뉴로 돌아가기
	auto goMenuLabel = Label::createWithSystemFont("메뉴", "DAON_2.28(L)", 20);
	auto Unititem1 = MenuItemLabel::create(goMenuLabel, CC_CALLBACK_1(GameOver::GoMenu, this));
	Unititem1->setColor(Color3B(0, 0, 0));
	Unititem1->setAnchorPoint(Vec2(0, 0));
	Unititem1->setPosition(Vec2(this->getContentSize().width - 700, 200));

	//게임 나가기
	auto exitGame = Label::createWithSystemFont("나가기", "DAON_2.28(L)", 20);
	auto Unititem2 = MenuItemLabel::create(exitGame, CC_CALLBACK_1(GameOver::Exitgame, this));
	Unititem2->setColor(Color3B(0, 0, 0));
	Unititem2->setAnchorPoint(Vec2(0, 0));
	Unititem2->setPosition(Vec2(this->getContentSize().width - 500, 200));

	auto menu = Menu::create(Unititem1, Unititem2, NULL);
	this->addChild(menu);

	return true;
}

void GameOver::createBackground()
{
	auto voidNode = Layer::create();
	auto back1 = Sprite::create("MenuBack.png");
	back1->setAnchorPoint(Vec2(0, 0));
	back1->setPosition(Vec2(-20, 0));
	back1->setScaleX(1.08f);
	back1->setScaleY(1.053f);

	auto back_Title = Sprite::create("back_Title.png");
	back_Title->setAnchorPoint(Vec2(0, 0));
	back_Title->setPosition(Vec2(120, 300));
	back_Title->setScale(2.0);

	//배경노드에 스프라이트를 넣는다
	voidNode->addChild(back1);

	//배경노드에 스프라이트를 넣는다
	voidNode->addChild(back_Title);

	//캐릭터보다 아래에 위치하도록 ZOrder 추가
	this->addChild(voidNode, 0);	
}

void GameOver::GoMenu(Ref* sender)
{
	Director::getInstance()->replaceScene(HelloWorld::createScene());
}

void GameOver::Exitgame(Ref* sender)
{
	exit(0);
}