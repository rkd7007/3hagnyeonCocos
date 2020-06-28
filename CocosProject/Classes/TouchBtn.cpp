#include "TouchBtn.h"

USING_NS_CC;


TouchBtn* TouchBtn::create(const std::string& filename)
{
	TouchBtn * sprite = new (std::nothrow) TouchBtn();
	//nothrow �� ���������� TouchBtn �� �������� ���� ��� ���α׷��� ���� �ʵ��� ����ó���� ����

	if (sprite && sprite->initWithFile(filename))
	{
		sprite->autorelease(); // ��������Ʈ ����� ���� �� �ڵ����� �޸𸮿��� ���ŵ� �� �ֵ��� ��
		return sprite;
	}

	CC_SAFE_DELETE(sprite); // ����� ���� ��������Ʈ�� ����
	return nullptr;
}

void TouchBtn::onEnter() //ȭ���� ��µɶ� ����
{
	Sprite::onEnter(); //�ݵ�� ���� ȣ��
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [=](Touch* touch, Event*event)
	{
		//onTouchBegan ������ �����Լ��� ó�� (���� 240, ��ġ���� ���� ���� -> ������(���������̵�))
		log("touch began");
		Vec2 LocationInNode = this->convertToNodeSpace(touch->getLocation());
		Size s = this->getContentSize(); //���ٷ� �۾������Ƿ� this�� ����
		Rect rect = Rect(0, 0, s.width, s.height);

		if (rect.containsPoint(LocationInNode)) //�ش���Ͱ� ��ġ�Ǿ��°�?
		{
			this->setColor(Color3B::RED);
			
			return true;
		}
	}; //�����Լ���

	   //onTouchMoved, onTouchEnded�� ���� �Լ��� �߰� (��ġ����� ���� ����->������ (���������̵�))

	listener->onTouchMoved = [=](Touch*touch, Event*event)
	{
		//this->setPosition(this->getPosition() + touch->getDelta()); //�̵��� ������ �ݿ�

		//															//move ������ �����;���
		//															//lod_position = touch -> getPreviousLocation();
	};

	listener->onTouchEnded = [=](Touch * touch, Event * evnet)
	{
		exit(0);
	};



	//��ġ �켱���� ��������� �����غ�(ó���� false�� ��Ʈ��, ���� ������ ����)

	if (_useNodePriority) //�켱������ �׷��� ������� �̸�
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this); //�׷��� �������
	else // �켱������ ������ ������ �ٱ��ٸ� (ó������)
		_eventDispatcher->addEventListenerWithFixedPriority(listener, _fixedPriority); // ������ �켱�������

	_listener = listener; //ȭ�� ���϶� ��ġ�ϸ� ������ ����� ȭ�� ������� ������ ����

}

void TouchBtn::onExit()
{
	_eventDispatcher->removeEventListener(_listener); //ȭ���� ������� ������ ����
	Sprite::onExit(); //�ݵ�� ȣ��
}

void TouchBtn::setPriority(int fixedPriority)
{
	//������ ������ ��ġ �켱������ �����ϰ��� �� �� ȣ��Ǵ� �޼���
	_fixedPriority = fixedPriority;
}

void TouchBtn::setPriorityWithThis(bool usenodePriority)
{
	//��ġ �켱 ������ ZORDER ������ �� ��, �־�� ���� �̿����� �����ϴ� �޼ҵ�
	_useNodePriority = usenodePriority;
}