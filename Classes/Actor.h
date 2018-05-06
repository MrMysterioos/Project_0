#include "cocos2d.h"
#include "ObjectManager.h"

class Actor: public Node {
protected:
	Sprite* _sprite; //������ ����� � ���� ����������� ������
	Map<std::string, Animation*> _animationsMap; //map ��������
	virtual void interaction() = 0;	//����������� ������� ��������������

	bool initWithBehavior(Behavior*);	//��� ������� ����� ���������� � ���� �����������
};