#include "GameOver.h"
#include "SimpleAudioEngine.h"
#include "InGame.h"
#include "HelloWorldScene.h"

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

	//�޴��� ���ư���
	auto goMenuLabel = Label::createWithSystemFont("�޴�", "DAON_2.28(L)", 20);
	auto Unititem1 = MenuItemLabel::create(goMenuLabel, CC_CALLBACK_1(GameOver::GoMenu, this));
	Unititem1->setColor(Color3B(0, 0, 0));
	Unititem1->setAnchorPoint(Vec2(0, 0));
	Unititem1->setPosition(Vec2(this->getContentSize().width - 700, 200));

	//���� ������
	auto exitGame = Label::createWithSystemFont("������", "DAON_2.28(L)", 20);
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

	//����忡 ��������Ʈ�� �ִ´�
	voidNode->addChild(back1);

	//����忡 ��������Ʈ�� �ִ´�
	voidNode->addChild(back_Title);

	//ĳ���ͺ��� �Ʒ��� ��ġ�ϵ��� ZOrder �߰�
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