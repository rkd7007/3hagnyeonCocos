#include "GameOver.h"
#include "SimpleAudioEngine.h"
#include "InGame.h"

USING_NS_CC;

//����� �ҽ� ���� ���ӽ����̽� ����
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

	SimpleAudioEngine::getInstance()->playBackgroundMusic("MainSound.mp3", true); //�ݺ��ؼ� ���
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

	//����忡 ��������Ʈ�� �ִ´�
	voidNode->addChild(back1);

	//����忡 ��������Ʈ�� �ִ´�
	voidNode->addChild(back_Title);

	//ĳ���ͺ��� �Ʒ��� ��ġ�ϵ��� ZOrder �߰�
	this->addChild(voidNode, 0);	
}