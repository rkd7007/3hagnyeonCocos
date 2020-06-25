#include "CreatePopUnitMix.h"
#include "InGame.h"
#include "CreatePopUnit.h"

USING_NS_CC;

bool CreatePopUnitMix::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto winSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();

	auto Pop = LayerColor::create(Color4B(0, 0, 255, 255));
	Pop->setScaleX(0.5);
	Pop->setScaleY(0.5);
	//Pop->setPosition(Point(winSize.width, winSize.height));
	this->addChild(Pop);

	//�ٶ� �Ӽ� ���� ���� �޴�
	auto label_Unit_wind = Label::createWithSystemFont("�ٶ� �Ӽ� ����", "DAON_2.28(L)", 50);
	auto Unititem1 = MenuItemLabel::create(label_Unit_wind, CC_CALLBACK_1(CreatePopUnitMix::MixUnit, this, 1));
	Unititem1->setColor(Color3B(0, 0, 0));
	Unititem1->setAnchorPoint(Vec2(0.5, 0.5));
	//Unititem1->setAnchorPoint(ccp(0.5f, 0.5f));
	Unititem1->setPosition(Vec2(50, 100));

	//�� �Ӽ� ���� ���� �޴�
	auto label_Unit_ground = Label::createWithSystemFont("�� �Ӽ� ����", "DAON_2.28(L)", 50);
	auto Unititem2 = MenuItemLabel::create(label_Unit_ground, CC_CALLBACK_1(CreatePopUnitMix::MixUnit, this, 2));
	Unititem2->setColor(Color3B(0, 0, 0));
	Unititem2->setAnchorPoint(Vec2(0.5, 0.5));
	//Unititem2->setAnchorPoint(ccp(0.5f, 0.5f));
	Unititem2->setPosition(Vec2(50, 50));

	//�� �Ӽ� ���� ���� �޴�
	auto label_Unit_fire = Label::createWithSystemFont("�� �Ӽ� ����", "DAON_2.28(L)", 50);
	auto Unititem3 = MenuItemLabel::create(label_Unit_fire, CC_CALLBACK_1(CreatePopUnitMix::MixUnit, this, 3));
	Unititem3->setColor(Color3B(0, 0, 0));
	Unititem3->setAnchorPoint(Vec2(0.5, 0.5));
	//Unititem3->setAnchorPoint(ccp(0.5f, 0.5f));
	Unititem3->setPosition(Vec2(50, 0));

	auto menu = Menu::create(Unititem1, Unititem2, Unititem3, NULL);
	this->addChild(menu);

	//�ΰ������� ���ư��� ���̺� ����
	auto menuitem = MenuItemFont::create("back", CC_CALLBACK_1(CreatePopUnitMix::BackInGame, this));
	auto go_ingamMenu = Menu::create(menuitem, NULL);
	go_ingamMenu->setAnchorPoint(Vec2(0, 0));
	go_ingamMenu->alignItemsVertically();
	go_ingamMenu->setPosition(Vec2(this->getContentSize().width / 2, 30));
	this->addChild(go_ingamMenu);

	return true;
}

void CreatePopUnitMix::BackInGame(Ref* sneder)
{
	this->removeFromParentAndCleanup(true); //���̾� ����
}

void CreatePopUnitMix::MixUnit(Ref* sneder, int unitNum)
{
	auto parent = (CreatePopUnit *)this->getParent(); //�θ� �����´�.

	switch (unitNum)
	{
	case 1:
	{
		if (parent->wind_1 >= 3)
		{
			parent->wind_1 -= 3;
			//�������� ���ְ� ���� 2 ������ ������Ų��
			//parent->doBuyWindUnit();
		}
	}
	break;
	case 2:
	{
		if (parent->ground_1 >= 3)
		{
			parent->ground_1 -= 3;
			//parent->doBuyWindUnit();
		}
	}
	break;
	case 3:
	{
		if (parent->fire_1 >= 3)
		{
			parent->fire_1 -= 3;
			//parent->doBuyWindUnit();
		}
	}
	break;
	}
	
		

	this->removeFromParentAndCleanup(true);
}
