#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "InGame.h"

USING_NS_CC;

//����� �ҽ� ���� ���ӽ����̽� ����
using namespace CocosDenshion;

Scene* HelloWorld::createScene()
{
	return HelloWorld::create();
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
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

	auto listener = EventListenerTouchOneByOne::create(); //�̺�Ʈ ������ ����
	listener->setSwallowTouches(true);

	//ó���� ���� ��ġ�� �̺�Ʈ���� ���ŵ�(z-order�� ���� ������Ʈ�� ��ġ �̺�Ʈ�� �����Ͽ� ó��)
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this); //�ʿ��� �ݹ��Լ� ���

																			//�����ʸ� �̺�Ʈ�����Ŀ� ���
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this); //this�� ������ǹ�, ȭ�鿡 �׷��� ������� ó��

	return true;
}

void HelloWorld::createBackground()
{
	auto voidNode = Layer::create();
	auto back1 = Sprite::create("MenuBack.png");
	back1->setAnchorPoint(Vec2(0, 0));
	back1->setPosition(Vec2(-20, 0));
	back1->setScaleX(1.08f);
	back1->setScaleY(1.053f);

	auto backLetter = Sprite::create("tapAny.png");
	backLetter->setAnchorPoint(Vec2(0, 0));
	backLetter->setPosition(Vec2(280, 30));
	backLetter->setScaleX(1.5f);

	auto blinkAction = Blink::create(0.9f, 1);
	auto repeatAction = RepeatForever::create(blinkAction);

	backLetter->runAction(repeatAction);

	auto back_Title = Sprite::create("back_Title.png");
	back_Title->setAnchorPoint(Vec2(0, 0));
	back_Title->setPosition(Vec2(120, 300));
	back_Title->setScale(2.0);

	//����忡 ��������Ʈ�� �ִ´�
	voidNode->addChild(back1);

	//����忡 ��������Ʈ�� �ִ´�
	voidNode->addChild(backLetter);

	//����忡 ��������Ʈ�� �ִ´�
	voidNode->addChild(back_Title);

	//ĳ���ͺ��� �Ʒ��� ��ġ�ϵ��� ZOrder �߰�
	this->addChild(voidNode, 0);	
}

bool HelloWorld::onTouchBegan(Touch*touch, Event *event)
{

	//��ġ �� ȭ����ȯ
	Director::getInstance()->replaceScene(InGame::createScene());


	return true;
}

