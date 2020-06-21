#ifndef __INGAME_H__
#define __INGAME_H__

#include "cocos2d.h"

USING_NS_CC;

//한글출력
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
	
	int count_enemy; //적이 몇마리 생성됐는지 카운트
	int E_time; //적 생성 시간
	int B_time; //총알 생성 시간
	
	int c_Xpoint; //캐릭터 x좌표
	int c_Ypoint; //캐릭터 y좌표
	
	int isTouchpointX; //터치 x좌표
	int isTouchpointY; //터치 y좌표
	
	int Bullet_y; //총알 y좌표
	int Bullet_x; //총알 x좌표
	
	int Enemy_x;
	int Enemy_y;
	int Hp = 5;
	
	int score;
	
	bool bChange;

	bool isTouch; //터치 했는지
	bool isCreatePly; //플레이어 유닛 생성되었는가
	bool MaxEnemy; //max까지 적이 생성됐는지

	void poplayer(Ref* sender); //유닛 선택하는 팝업창 생성

	void c_MoveToTouch(); //터치한 곳으로 캐릭터 이동시키는 함수
	bool onTouchBegan(Touch* touch, Event* event); //터치 좌표 받아오는 함수
	
	void doBuyWindUnit(Ref*sender);

	//적
	cocos2d::Sprite* pEnemy; //적 이미지
	void createEnemy(); //적 만듦 - 참고 : https://rudalstb.tistory.com/74
	
	void tick1(float f);
	
	//플레이어 (유닛)
	cocos2d::Sprite* unitWind1; //플레이어 이미지
	void createPlayer(); //플레이어 만듦

	cocos2d::Sprite* pBullet; //총알 이미지
	void createBullet(); //총알 만듦
	
	//점수
	cocos2d::Label* score_label; //점수
	cocos2d::Label* killenemy_label; //죽인 적의 수

	// implement the "static create()" method manually
	CREATE_FUNC(InGame);
};

#endif