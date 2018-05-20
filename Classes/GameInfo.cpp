#include "GameInfo.h"
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
	if (doc.Error())
		return false;

	XMLNode* eSave = doc.FirstChildElement("Save");
	if (eSave) {
		XMLNode* eHeroes = eSave->FirstChildElement("heroes");
		if (eHeroes) {
			XMLNode* eHero = eHeroes->FirstChildElement("character");
			while (eHero) {
				// init heroes
				ObjectInfo tempHero;
				tempHero.initWithXmlElement(eHero);
<<<<<<< HEAD

				_heroes.push_back(tempHero);

=======

				_heroes.push_back(tempHero);

>>>>>>> f_scene
				eHero = eHero->NextSiblingElement("character");
			}
		}
		else
			return false;
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
		else
			return false;
		XMLNode* resources = eSave->FirstChildElement("resources");
		if (resources) {
			// init res
			_totalTime = atoi(resources->Attribute("total_time"));
			_gold = atoi(resources->Attribute("gold"));
			_provision = atoi(resources->Attribute("provision"));
		}
		else
			return false;
		XMLNode* level = eSave->FirstChildElement("level");
		if (level) {
			// init level
			std::string levelSource = level->Attribute("source");
			LevelInfo* tempLevel = LevelInfo::create(levelSource);
			_level = tempLevel;
			_level->retain();
			_curAct = atoi(level->Attribute("act_id"));
		}
		else
			return false;

	}
	else
		return false;

	return true;
}