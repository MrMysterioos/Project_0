#include "CampFire.h"

USING_NS_CC;

/*CampFire::CampFire(FireInfo fire)
{

};*/

CampFire* CampFire::createWithName(std::string key)
{
	_node = Node::create();
	//Нужны данные о кострах
	return this;
}