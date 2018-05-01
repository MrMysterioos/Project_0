#include "ObjInfo.h"
#include "tinyxml2\tinyxml2.h"

ObjectInfo::ObjectInfo()
	: _bInit(false)
{}

bool ObjectInfo::initWithXmlElement(tinyxml2::XMLElement* node) {
	typedef tinyxml2::XMLDocument XMLDoc;
	typedef tinyxml2::XMLElement XMLNode;

	if (!node)
		return false;

	std::string name = node->Name();
	_typeName = name;

	auto att = node->FirstAttribute();
	while (att) {
		std::string name = att->Name();
		std::string value = att->Value();
		_info.insert(std::pair<std::string, std::string>(name, value));
		att = att->Next();
	}

	_bInit = true;

	return true;
}