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

bool ObjectInfo::initWithElementId(std::string file, std::string id) {
	using XMLDoc = tinyxml2::XMLDocument;
	using XMLElement = tinyxml2::XMLElement;

	XMLDoc doc;
	doc.LoadFile(file.c_str());
	if (doc.Error())
		return false;
	XMLElement* root = doc.FirstChildElement();
	if (root) {
		XMLElement* e = root->FirstChildElement();
		while (e) {
			std::string otherId = e->Attribute("id");
			if (otherId == id) {
				initWithXmlElement(e);
				return true;
			}
			e = e->NextSiblingElement();
		}
	}
	return false;
}