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

	void BaseFunc();

	void update(float f);

	int c_Xpoint; //캐릭터 x좌표
	int c_Ypoint; //캐릭터 y좌표
	
	int testPointX[30]; 
	int testPointY[30];
	int testCount = 0;

	bool bChange;
	//bool bChange2;

	//터치--------------------------------------------------------
	void c_MoveToTouch(); //터치한 곳으로 캐릭터 이동시키는 함수
	bool onTouchBegan(Touch* touch, Event* event); //터치 좌표 받아오는 함수
	int isTouchpointX; //터치 x좌표
	int isTouchpointY; //터치 y좌표

	//팝업창--------------------------------------------------------
	void popUnit(Ref* sender); //유닛 구매하는 팝업 창
	void popuplayer(Ref*sender); //게임 오버 팝업 창
	void popuplayer_stage(Ref*sender); //스테이지클리어 팝업 창

	//적--------------------------------------------------------
	cocos2d::Sprite* pEnemy; //적 이미지
	//cocos2d::Sprite* pEnemy2; //적 이미지
	void createEnemy(); //적 만듦 - 참고 : https://rudalstb.tistory.com/74
	void createEnemy2();
	int count_enemy; //적이 몇마리 생성됐는지 카운트
	bool MaxEnemy; //max까지 적이 생성됐는지
	int Hp = 5;
	int E_time; //적 생성 시간
	int Enemy_x;
	int Enemy_y;

	//int Enemy_x2;
	//int Enemy_y2;

	//유닛--------------------------------------------------------
	cocos2d::Sprite* unitWind[30]; //플레이어 이미지
	cocos2d::Sprite* unitGrass[30]; //플레이어 이미지
	int indexUnit;
	void createUnit(); //초기 세마리 유닛 만듦
	void doBuyWindUnit(std::string tableName);
	bool start_count;

	//체력--------------------------------------------------------
	cocos2d::Label* Hp_label; //체력
	int hp_count;

	//총알--------------------------------------------------------
	cocos2d::Sprite* pBullet[30]; //총알 이미지
	int indexBullet;
	void createBullet(); //총알 만듦
	int B_time; //총알 생성 시간
	int Bullet_x[20];
	int Bullet_y[20];

	//코인--------------------------------------------------------
	cocos2d::Label* coin_label; //점수
	int myCoin;

	//시간--------------------------------------------------------
	cocos2d::Label*timer_label;
	int time_count;
	void timer(float f);
	void timer_for_monsterOut(float f);
	void tick1(float f);

	// implement the "static create()" method manually
	CREATE_FUNC(InGame);
};

#endif