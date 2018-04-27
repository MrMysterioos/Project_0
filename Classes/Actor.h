#include "cocos2d.h"
#include "ObjectManager.h"

class Actor: public Node {
protected:
	Sprite* _sprite; //������ ����� � ���� ����������� ������
	std::map<std::string, std::string> _animates;	//map ��������

public:
	virtual void interaction() = 0;	//����������� ������� ��������������
};