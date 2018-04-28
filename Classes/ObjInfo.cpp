#include "ObjInfo.h"
#include "tinyxml2\tinyxml2.h"

ObjectInfo* ObjectInfo::create(tinyxml2::XMLDocument& doc, std::string id) {
	ObjectInfo* ret = new (std::nothrow) ObjectInfo();
	if (ret->init(doc, id)) {
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool ObjectInfo::init(tinyxml2::XMLDocument& doc, std::string id) {
	typedef tinyxml2::XMLDocument XMLDoc;
	typedef tinyxml2::XMLElement XMLNode;

	XMLNode* eObjects = doc.FirstChildElement("Objects");
	if (eObjects) {
		XMLNode* eObject = eObjects->FirstChildElement();
		while (eObject) {
			std::string otherId = eObject->Attribute("id");
			if (otherId == id) {
				auto att = eObject->FirstAttribute();
				while (att) {
					std::string name = att->Name();
					std::string value = att->Value();
					_info.insert(std::pair<std::string, std::string>(name, value));
					att = att->Next();
				}
				return true;
			}
			eObject = eObject->NextSiblingElement();
		}
	}
	return false;
}

Behavior* Behavior::create() {
	Behavior* ret = new (std::nothrow) Behavior();
	ret->autorelease();
	return ret;
}