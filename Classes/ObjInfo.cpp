#include "ObjInfo.h"
/*
CharInfo::CharInfo()
	: health(10)
	, speed(10)
	, damage(10)
	, level(0)
	, experience(0)
{}
*/
CharInfo* CharInfo::create(std::string name) {
	CharInfo* ret = new (std::nothrow) CharInfo();
	ret->autorelease();
	return ret;
}