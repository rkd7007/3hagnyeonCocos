#pragma once
#include "cocos2d.h"

class TouchBtn : public cocos2d::Sprite //Sprite�� ��ӹ���
{
public:
	static TouchBtn* create(const std::string & filename);
	void setPriority(int fixedPriority);
	void setPriorityWithThis(bool useNodePriority);

	//ȭ���� ���̰ų� ����� �� ȣ��
	void onEnter();
	void onExit();

	int touchCount = 0;



private:
	cocos2d::EventListener* _listener; // ���Ͱ� ��ġó��
	int _fixedPriority; //��ġ�켱���� ������
	bool _useNodePriority; // �켱������ ���ϴ� ���(2����)

}; //��ġó���Լ��� ���ٷ� ó���� ����