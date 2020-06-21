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

	int time_count;

	void timer(float f);
	void BaseFunc();

	cocos2d::Label*timer_label;

	void update(float f);
	
	int count_enemy; //���� ��� �����ƴ��� ī��Ʈ
	int E_time; //�� ���� �ð�
	int B_time; //�Ѿ� ���� �ð�
	
	int c_Xpoint; //ĳ���� x��ǥ
	int c_Ypoint; //ĳ���� y��ǥ
	
	int isTouchpointX; //��ġ x��ǥ
	int isTouchpointY; //��ġ y��ǥ
	
	int Bullet_y; //�Ѿ� y��ǥ
	int Bullet_x; //�Ѿ� x��ǥ
	
	int Enemy_x;
	int Enemy_y;
	int Hp = 5;
	
	int score;
	
	bool bChange;

	bool isTouch; //��ġ �ߴ���
	bool isCreatePly; //�÷��̾� ���� �����Ǿ��°�
	bool MaxEnemy; //max���� ���� �����ƴ���

	void poplayer(Ref* sender); //���� �����ϴ� �˾�â ����

	void c_MoveToTouch(); //��ġ�� ������ ĳ���� �̵���Ű�� �Լ�
	bool onTouchBegan(Touch* touch, Event* event); //��ġ ��ǥ �޾ƿ��� �Լ�
	
	void doBuyWindUnit(Ref*sender);

	//��
	cocos2d::Sprite* pEnemy; //�� �̹���
	void createEnemy(); //�� ���� - ���� : https://rudalstb.tistory.com/74
	
	void tick1(float f);
	
	//�÷��̾� (����)
	cocos2d::Sprite* unitWind1; //�÷��̾� �̹���
	void createPlayer(); //�÷��̾� ����

	cocos2d::Sprite* pBullet; //�Ѿ� �̹���
	void createBullet(); //�Ѿ� ����
	
	//����
	cocos2d::Label* score_label; //����
	cocos2d::Label* killenemy_label; //���� ���� ��

	// implement the "static create()" method manually
	CREATE_FUNC(InGame);
};

#endif