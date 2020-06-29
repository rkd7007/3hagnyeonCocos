#include "CreatePopUnit.h"
#include "InGame.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

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

	/*
	//�ٶ��Ӽ����ֱ��� �޴�
	auto label_Unit_wind = Label::createWithSystemFont("�ٶ� �Ӽ�", "DAON_2.28(L)", 50);
	auto Unititem1 = MenuItemLabel::create(label_Unit_wind, CC_CALLBACK_1(CreatePopUnit::CreateUnit, this, 1));
	Unititem1->setColor(Color3B(0, 0, 0));
	Unititem1->setAnchorPoint(Vec2(0.5, 0.5));
	//Unititem1->setAnchorPoint(ccp(0.5f, 0.5f));
	Unititem1->setPosition(Vec2(50, 100));

	//���Ӽ����ֱ��� �޴�
	auto label_Unit_ground = Label::createWithSystemFont("�� �Ӽ�", "DAON_2.28(L)", 50);
	auto Unititem2 = MenuItemLabel::create(label_Unit_ground, CC_CALLBACK_1(CreatePopUnit::CreateUnit, this, 2));
	Unititem2->setColor(Color3B(0, 0, 0));
	Unititem2->setAnchorPoint(Vec2(0.5, 0.5));
	//Unititem2->setAnchorPoint(ccp(0.5f, 0.5f));
	Unititem2->setPosition(Vec2(50, 50));

	//�ҼӼ����ֱ��� �޴�
	auto label_Unit_fire = Label::createWithSystemFont("�� �Ӽ�", "DAON_2.28(L)", 50);
	auto Unititem3 = MenuItemLabel::create(label_Unit_fire, CC_CALLBACK_1(CreatePopUnit::CreateUnit, this, 3));
	Unititem3->setColor(Color3B(0, 0, 0));
	Unititem3->setAnchorPoint(Vec2(0.5, 0.5));
	//Unititem3->setAnchorPoint(ccp(0.5f, 0.5f));
	Unititem3->setPosition(Vec2(50, 0));

	auto menu = Menu::create(Unititem1, Unititem2, Unititem3, NULL);
	this->addChild(menu);

	//�ΰ������� ���ư��� ���̺� ����
	auto menuitem = MenuItemFont::create("back", CC_CALLBACK_1(CreatePopUnit::BackInGame, this));
	auto go_ingamMenu = Menu::create(menuitem, NULL);
	go_ingamMenu->setAnchorPoint(Vec2(0, 0));
	go_ingamMenu->alignItemsVertically();
	go_ingamMenu->setPosition(Vec2(this->getContentSize().width / 2, 30));
	this->addChild(go_ingamMenu);
	*/

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
		table = "fish";
	break;
	case 2:
		table = "mush";
	break;
	case 3:
		table = "grass";
	break;
	case 4:
		table = "wood";
	break;
	case 5:
		table = "cat";
	break;
	case 6:
		table = "tiger";
	break;
	}

	/*switch (unitNum)
	{
	case 1:
	{
		if (parent->myCoin >= 10)
		{
			parent->myCoin -= 10;
			table = "fish";
		}
	}
	break;
	case 2:
	{
		if (parent->myCoin >= 20)
		{
			parent->myCoin -= 20;
			table = "mush";
		}
	}
	break;
	case 3:
	{
		if (parent->myCoin >= 10)
		{
			parent->myCoin -= 10;
			table = "grass";
		}
	}
	break;
	case 4:
	{
		if (parent->myCoin >= 20)
		{
			parent->myCoin -= 20;
			table = "wood";
		}
	}
	break;
	case 5:
	{
		if (parent->myCoin >= 10)
		{
			parent->myCoin -= 10;
			table = "cat";
		}
	}
	break;
	case 6:
	{
		if (parent->myCoin >= 20)
		{
			parent->myCoin -= 20;
			table = "tiger";
		}
	}
	break;
	}*/
	
	auto parent = (InGame *)this->getParent(); //�θ� �����´�.
	parent->doBuyWindUnit(table); //�θ��� �޼��带 ȣ���Ѵ�.

	this->removeFromParentAndCleanup(true);
}
