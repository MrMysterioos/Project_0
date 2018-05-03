#include "cocos2d.h"
#include "ObjectManager.h"

class Actor: public Node {
protected:
	Sprite* _sprite; //������ ����� � ���� ����������� ������
	Map<std::string, Animation*> _animationsMap; //map ��������
	Animate* _animate; // ��������
	virtual void interaction() = 0;	//����������� ������� ��������������

	bool initWithBehavior(Behavior*);	//��� ������� ����� ���������� � ���� �����������
};