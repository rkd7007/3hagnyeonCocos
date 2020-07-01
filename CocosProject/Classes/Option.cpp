#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Option.h"

USING_NS_CC;

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Option::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto winSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();

	//How Play Game ÆË¾÷ Ã¢
	auto Pop = Sprite::create("popOption.png");
	Pop->setAnchorPoint(Vec2(0, 0));
	Pop->setScaleX(0.22);
	Pop->setScaleY(0.22);
	Pop->setPosition(Vec2(80, -20));
	this->addChild(Pop);

	//x¹öÆ°
	auto backBut = MenuItemImage::create("xButton.png", "xButton_click.png", [&](Ref *sender) {this->removeFromParentAndCleanup(true); });
	backBut->setAnchorPoint(Vec2(0, 0));
	backBut->setPosition(Vec2(800, 500));
	backBut->setScale(0.23);

	auto menu = Menu::create(backBut, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

	return true;
}