#ifndef __INGAME_H__
#define __INGAME_H__

#include "cocos2d.h"

USING_NS_CC;

//�ѱ����
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif


class InGame : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	//Size size;

	void BaseFunc();

	void update(float f);

	int c_Xpoint; //ĳ���� x��ǥ
	int c_Ypoint; //ĳ���� y��ǥ
	
	int testPointX[30]; 
	int testPointY[30];
	int testCount = 0;

	bool bChange;
	
	//��ġ--------------------------------------------------------
	void c_MoveToTouch(); //��ġ�� ������ ĳ���� �̵���Ű�� �Լ�
	bool onTouchBegan(Touch* touch, Event* event); //��ġ ��ǥ �޾ƿ��� �Լ�
	int isTouchpointX; //��ġ x��ǥ
	int isTouchpointY; //��ġ y��ǥ

	//�˾�â--------------------------------------------------------
	void popUnit(Ref* sender); //���� �����ϴ� �˾�â
	void popUnitMix(Ref* sender); //���� �����ϴ� �˾�â
	void popUnitAll(Ref* sender); //��� ���� ���� �˾�â

	//��--------------------------------------------------------
	cocos2d::Sprite* pEnemy; //�� �̹���
	void createEnemy(); //�� ���� - ���� : https://rudalstb.tistory.com/74
	int count_enemy; //���� ��� �����ƴ��� ī��Ʈ
	bool MaxEnemy; //max���� ���� �����ƴ���
	int Hp = 5;
	int E_time; //�� ���� �ð�
	int Enemy_x;
	int Enemy_y;

	//����--------------------------------------------------------
	cocos2d::Sprite* unitWind[30]; //�÷��̾� �̹���
	int indexUnit;
	void createUnit(); //�ʱ� ������ ���� ����
	void doBuyWindUnit(std::string tableName);
	bool start_count;
	//�Ѿ�--------------------------------------------------------
	cocos2d::Sprite* pBullet[30]; //�Ѿ� �̹���
	int indexBullet;
	void createBullet(); //�Ѿ� ����
	int B_time; //�Ѿ� ���� �ð�
	int Bullet_x;
	int Bullet_y;

	//����--------------------------------------------------------
	cocos2d::Label* score_label; //����
	int score;
	//cocos2d::Label* killenemy_label; //���� ���� ��

	//�ð�--------------------------------------------------------
	cocos2d::Label*timer_label;
	int time_count;
	void timer(float f);
	void timer_for_monsterOut(float f);
	void tick1(float f);

	// implement the "static create()" method manually
	CREATE_FUNC(InGame);
};

#endif