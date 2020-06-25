#include "GameOver.h"
#include "SimpleAudioEngine.h"
#include "InGame.h"

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