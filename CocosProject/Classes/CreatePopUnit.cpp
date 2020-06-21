#include "CreatePopUnit.h"
#include "InGame.h"

USING_NS_CC;

bool CreatePopUnit::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto Pop = LayerColor::create(Color4B(0, 0, 255, 255));
	this->addChild(Pop);

	auto label = Label::createWithSystemFont("Chose Unit", "Thonburi", 24);
	label->setPosition(Vec2(this->getContentSize().width / 2, 50));
	this->addChild(label);

	//�ٶ��Ӽ����ֱ��� �޴�
	auto label_Unit_wind = Label::createWithSystemFont("�ٶ� �Ӽ�", "DAON_2.28(L)", 30);
	auto Unititem1 = MenuItemLabel::create(label_Unit_wind, CC_CALLBACK_1(CreatePopUnit::ChagneWindBool, this));
	Unititem1->setColor(Color3B(0, 0, 0));
	Unititem1->setAnchorPoint(Vec2(0.5, 0.5));
	Unititem1->setPosition(Vec2(100, 240));


	//���Ӽ����ֱ��� �޴�
	auto label_Unit_ground = Label::createWithSystemFont("�� �Ӽ�", "DAON_2.28(L)", 30);
	auto Unititem2 = MenuItemLabel::create(label_Unit_ground, CC_CALLBACK_1(CreatePopUnit::ChagneGroundBool, this));
	Unititem2->setColor(Color3B(0, 0, 0));
	Unititem2->setAnchorPoint(Vec2(0.5, 0.5));
	Unititem2->setPosition(Vec2(260, 240));


	//�ҼӼ����ֱ��� �޴�
	auto label_Unit_fire = Label::createWithSystemFont("�� �Ӽ�", "DAON_2.28(L)", 30);
	auto Unititem3 = MenuItemLabel::create(label_Unit_fire, CC_CALLBACK_1(CreatePopUnit::ChagneFireBool, this));
	Unititem3->setColor(Color3B(0, 0, 0));
	Unititem3->setAnchorPoint(Vec2(0.5, 0.5));
	Unititem3->setPosition(Vec2(400, 240));

	auto menu = Menu::create(Unititem1, Unititem2, Unititem3, NULL);
	this->addChild(menu);

	//�ΰ������� ���ư��� ���̺� ����
	auto menuitem = MenuItemFont::create("back", CC_CALLBACK_1(CreatePopUnit::BackInGame, this));
	auto go_ingamMenu = Menu::create(menuitem, NULL);
	go_ingamMenu->setAnchorPoint(Vec2(0, 0));
	go_ingamMenu->alignItemsVertically();
	go_ingamMenu->setPosition(Vec2(this->getContentSize().width / 2, 30));
	this->addChild(go_ingamMenu);

	return true;
}

void CreatePopUnit::BackInGame(Ref* sneder)
{
	this->removeFromParentAndCleanup(true); //���̾� ����
}

void CreatePopUnit::ChagneWindBool(Ref* sneder)
{
	isWind = true;
}

void CreatePopUnit::ChagneFireBool(Ref* sneder)
{
	isFire = true;
}

void CreatePopUnit::ChagneGroundBool(Ref* sneder)
{
	isGround = true;
}
