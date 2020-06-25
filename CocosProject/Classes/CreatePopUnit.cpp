#include "CreatePopUnit.h"
#include "InGame.h"

USING_NS_CC;

bool CreatePopUnit::init()
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
	
	/*
	����Ʈ ��
	https://cocos2dx.tistory.com/entry/cocos2dx-%EC%A2%8C%ED%91%9C%EA%B3%84-Position%EA%B3%BC-Anchor
	https://hyunity3d.tistory.com/231
	*/
	
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

	return true;
}

void CreatePopUnit::BackInGame(Ref* sneder)
{
	this->removeFromParentAndCleanup(true); //���̾� ����
}

void CreatePopUnit::CreateUnit(Ref* sneder, int unitNum)
{
	std::string table;

	switch (unitNum)
	{
	case 1:
	{
		table = "wind";
		wind_1 += 1;
	}
	break;
	case 2:
	{
		table = "ground";
		ground_1 += 1;
	}
	break;
	case 3:
	{
		table = "fire";
		fire_1 += 1;
	}
	break;
	}

	auto parent = (InGame *)this->getParent(); //�θ� �����´�.
	parent->doBuyWindUnit(table); //�θ��� �޼��带 ȣ���Ѵ�.

	this->removeFromParentAndCleanup(true);
}
