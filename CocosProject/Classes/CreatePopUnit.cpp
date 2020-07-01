#include "CreatePopUnit.h"
#include "InGame.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

extern int myCoin;

//����� �ҽ� ���� ���ӽ����̽� ����
using namespace CocosDenshion;

bool CreatePopUnit::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto winSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();

	//���� ���� �˾� â
	auto Pop = Sprite::create("buyUnit.png");
	Pop->setAnchorPoint(Vec2(0, 0));
	Pop->setScaleX(0.15);
	Pop->setScaleY(0.15);
	Pop->setPosition(Vec2(200, 40));
	this->addChild(Pop);

	//x��ư
	auto backBut = MenuItemImage::create("xButton.png", "xButton_click.png", [&](Ref *sender) {this->removeFromParentAndCleanup(true); });
	backBut->setAnchorPoint(Vec2(0, 0));
	backBut->setPosition(Vec2(650, 400));
	backBut->setScale(0.13);

	//����� - �� 1
	auto fish_plank = MenuItemImage::create("fish_plank.png", "fish_plank_click.png", CC_CALLBACK_1(CreatePopUnit::CreateUnit, this, 1));
	fish_plank->setAnchorPoint(Vec2(0, 0));
	fish_plank->setPosition(Vec2(340, 270));
	fish_plank->setScale(0.67);
	//���� - �� 2
	auto mush_plank = MenuItemImage::create("mush_plank.png", "mush_plank_click.png", CC_CALLBACK_1(CreatePopUnit::CreateUnit, this, 2));
	mush_plank->setAnchorPoint(Vec2(0, 0));
	mush_plank->setPosition(Vec2(490, 268));
	mush_plank->setScale(0.66);

	//������ - �� 1
	auto grass_plank = MenuItemImage::create("grass_plank.png", "grass_plank_click.png", CC_CALLBACK_1(CreatePopUnit::CreateUnit, this, 3));
	grass_plank->setAnchorPoint(Vec2(0, 0));
	grass_plank->setPosition(Vec2(345, 165));
	grass_plank->setScale(0.66);
	//���� - �� 2
	auto wood_plank = MenuItemImage::create("wood_plank.png", "wood_plank_click.png", CC_CALLBACK_1(CreatePopUnit::CreateUnit, this, 4));
	wood_plank->setAnchorPoint(Vec2(0, 0));
	wood_plank->setPosition(Vec2(490, 165));
	wood_plank->setScale(0.66);

	//����� - �� 1
	auto cat_plank = MenuItemImage::create("cat_plank.png", "cat_plank_click.png", CC_CALLBACK_1(CreatePopUnit::CreateUnit, this, 5));
	cat_plank->setAnchorPoint(Vec2(0, 0));
	cat_plank->setPosition(Vec2(340, 60));
	cat_plank->setScale(0.66);
	//���׶��� - �� 2
	auto tiger_plank = MenuItemImage::create("tiger_plank.png", "tiger_plank_click.png", CC_CALLBACK_1(CreatePopUnit::CreateUnit, this, 6));
	tiger_plank->setAnchorPoint(Vec2(0, 0));
	tiger_plank->setPosition(Vec2(490, 58));
	tiger_plank->setScale(0.66);

	auto menu = Menu::create(backBut, fish_plank, mush_plank, grass_plank, wood_plank, cat_plank, tiger_plank, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

	return true;
}

void CreatePopUnit::CreateUnit(Ref* sneder, int unitNum)
{
	SimpleAudioEngine::getInstance()->preloadEffect("Cash Register.wav"); //�޸𸮿� ȿ���� ����
	SimpleAudioEngine::getInstance()->playEffect("Cash Register.wav", false); //ȿ�������

	std::string table;

	switch (unitNum)
	{
	case 1:
	{
		if (myCoin >= 10)
		{
			myCoin -= 10;
			table = "fish";
		}
	}
	break;
	case 2:
	{
		if (myCoin >= 20)
		{
			myCoin -= 20;
			table = "mush";
		}
	}
	break;
	case 3:
	{
		if (myCoin >= 10)
		{
			myCoin -= 10;
			table = "grass";
		}
	}
	break;
	case 4:
	{
		if (myCoin >= 20)
		{
			myCoin -= 20;
			table = "wood";
		}
	}
	break;
	case 5:
	{
		if (myCoin >= 10)
		{
			myCoin -= 10;
			table = "cat";
		}
	}
	break;
	case 6:
	{
		if (myCoin >= 20)
		{
			myCoin -= 20;
			table = "tiger";
		}
	}
	break;
	}
	
	auto parent = (InGame *)this->getParent(); //�θ� �����´�.
	parent->doBuyWindUnit(table); //�θ��� �޼��带 ȣ���Ѵ�.

	this->removeFromParentAndCleanup(true);

	SimpleAudioEngine::getInstance()->unloadEffect("Cash Register.wav");
}
