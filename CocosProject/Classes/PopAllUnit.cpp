#include "PopAllUnit.h"
#include "InGame.h"
#include "CreatePopUnit.h"

USING_NS_CC;

bool PopAllUnit::init()
{
	if (!Layer::init())
	{
		return false;
	}

	/*auto Pop = LayerColor::create(Color4B(0, 0, 255, 255));
	Pop->setScaleX(0.8);
	Pop->setScaleY(0.5);
	Pop->setAnchorPoint(Vec2(0, 0));
	Pop->setPosition(Vec2(this->getContentSize().width - 580, this->getContentSize().height - 680));
	this->addChild(Pop);*/

	WhatUnit(this, 1);

	//�ٶ��Ӽ�����
	auto label_Unit_wind = Label::createWithSystemFont("�ٶ�", "DAON_2.28(L)", 20);
	auto Unititem1 = MenuItemLabel::create(label_Unit_wind, CC_CALLBACK_1(PopAllUnit::WhatUnit, this, 1));
	Unititem1->setColor(Color3B(0, 0, 0));

	//���Ӽ�����
	auto label_Unit_ground = Label::createWithSystemFont("��", "DAON_2.28(L)", 20);
	auto Unititem2 = MenuItemLabel::create(label_Unit_ground, CC_CALLBACK_1(PopAllUnit::WhatUnit, this, 2));
	Unititem2->setColor(Color3B(0, 0, 0));

	//�ҼӼ�����
	auto label_Unit_fire = Label::createWithSystemFont("��", "DAON_2.28(L)", 20);
	auto Unititem3 = MenuItemLabel::create(label_Unit_fire, CC_CALLBACK_1(PopAllUnit::WhatUnit, this, 3));
	Unititem3->setColor(Color3B(0, 0, 0));

	auto menu = Menu::create(Unititem1, Unititem2, Unititem3, NULL);
	menu->setAnchorPoint(Vec2(0, 0));
	menu->setPosition(Vec2(this->getContentSize().width - 500, 150));
	menu->alignItemsHorizontally();
	this->addChild(menu);

	//�ΰ������� ���ư��� ���̺� ���� -> X ui�� �����Ұ���
	auto menuitem = MenuItemFont::create("back", CC_CALLBACK_1(PopAllUnit::BackInGame, this));
	auto go_ingamMenu = Menu::create(menuitem, NULL);
	go_ingamMenu->setAnchorPoint(Vec2(0, 0));
	go_ingamMenu->setPosition(Vec2(this->getContentSize().width - 50, 150));
	this->addChild(go_ingamMenu);

	return true;
}

void PopAllUnit::BackInGame(Ref* sneder)
{
	this->removeFromParentAndCleanup(true); //���̾� ����
}

void PopAllUnit::WhatUnit(Ref* sneder, int unitNum)
{
	auto parent = (CreatePopUnit *)this->getParent(); //�θ� �����´�.

	switch (unitNum)
	{
	case 1: //�ٶ�
	{
		auto Pop = LayerColor::create(Color4B(255, 0, 0, 255));
		Pop->setScaleX(0.8);
		Pop->setScaleY(0.5);
		Pop->setAnchorPoint(Vec2(0, 0));
		Pop->setPosition(Vec2(this->getContentSize().width - 580, this->getContentSize().height - 680));
		this->addChild(Pop);
	}
	break;
	case 2: //��
	{
		auto Pop = LayerColor::create(Color4B(0, 255, 0, 255));
		Pop->setScaleX(0.8);
		Pop->setScaleY(0.5);
		Pop->setAnchorPoint(Vec2(0, 0));
		Pop->setPosition(Vec2(this->getContentSize().width - 580, this->getContentSize().height - 680));
		this->addChild(Pop);

		/*for (int i = 0; i < parent->ground_1; i++)
		{
			auto testSquare = CCSprite::create("HelloWorld.png", CCRect(0, 0, 100, 100));
			testSquare->setAnchorPoint(Vec2(0, 0));
			testSquare->setPosition(Vec2(600, this->getContentSize().height - 650));
			this->addChild(testSquare);
		}*/
	}
	break;
	case 3: //��
	{
		auto Pop = LayerColor::create(Color4B(0, 0, 255, 255));
		Pop->setScaleX(0.8);
		Pop->setScaleY(0.5);
		Pop->setAnchorPoint(Vec2(0, 0));
		Pop->setPosition(Vec2(this->getContentSize().width - 580, this->getContentSize().height - 680));
		this->addChild(Pop);
	}
	break;
	}
}
