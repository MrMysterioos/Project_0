#include "GameInfo.h"
#include "ObjectManager.h"
#include "tinyxml2\tinyxml2.h"

USING_NS_CC;

static GameInfo* _gameInfo = nullptr;

GameInfo* GameInfo::getInstance() {

	if (!_gameInfo) {
		_gameInfo = new (std::nothrow) GameInfo();
		_gameInfo->init();
	}

	return _gameInfo;
}

void GameInfo::destroyInstance()
{
	if (!_gameInfo) {
		_gameInfo->_destroy();
		CC_SAFE_RELEASE_NULL(_gameInfo);
	}
}

bool GameInfo::init() {

	return true;
}

void GameInfo::_destroy() {
	while (_level) {
		_level->release();
	}
}

bool GameInfo::initWithFile(std::string source) {
	typedef tinyxml2::XMLDocument XMLDoc;
	typedef tinyxml2::XMLElement XMLNode;

	std::string saveSource = source + "/save.xml";

	XMLDoc doc;
	doc.LoadFile(saveSource.c_str());

	XMLNode* eSave = doc.FirstChildElement("Save");
	if (eSave) {
		XMLNode* heroes = eSave->FirstChildElement("heroes");
		if (heroes) {
			XMLNode* eHero = heroes->FirstChildElement("hero");
			while (eHero) {
				// init heroes
				std::string heroesSource = source + "/heroes.xml";

				XMLDoc objDoc;
				objDoc.LoadFile(heroesSource.c_str());

				if (objDoc.Error())
					return false;

				std::string tempId = eHero->Attribute("template");
				ObjectInfo* tempHero = ObjectInfo::create(objDoc, tempId);

				Behavior* tempBehav = Behavior::create();
				tempBehav->baseObject = tempHero;
				std::string heroName = eHero->Attribute("name");
				tempBehav->name = heroName;

				_heroes.pushBack(tempBehav);
				
				eHero = eHero->NextSiblingElement("hero");
			}
		}
		XMLNode* artifacts = eSave->FirstChildElement("artifacts");
		if (artifacts) {
			XMLNode* artifact = artifacts->FirstChildElement("artifact");
			while (artifact) {
				// init artifacts
				std::string id = artifact->Attribute("id");
				_artifacts.push_back(id);
				artifact = artifact->NextSiblingElement("artifact");
			}
		}
		XMLNode* resources = eSave->FirstChildElement("resources");
		if (resources) {
			// init res
			_totalTime = atoi(resources->Attribute("total_time"));
			_gold = atoi(resources->Attribute("gold"));
			_provision = atoi(resources->Attribute("provision"));
		}
		XMLNode* level = eSave->FirstChildElement("level");
		if (level) {
			// init level
			std::string levelSource = level->Attribute("source");
			LevelInfo* tempLevel = LevelInfo::create(levelSource);
			_level = tempLevel;
			_level->retain();
			_curAct = atoi(level->Attribute("act_id"));
		}

	}

	return true;
}
