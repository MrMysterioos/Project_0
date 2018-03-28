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
	CC_SAFE_RELEASE_NULL(_gameInfo);
}

bool GameInfo::init() {



	return true;
}

bool GameInfo::initWithFile(std::string file) {
	typedef tinyxml2::XMLDocument XMLDoc;
	typedef tinyxml2::XMLElement XMLNode;
	
	std::string path = "saves/" + file;

	XMLDoc doc;
	doc.LoadFile(path.c_str());

	XMLNode* save = doc.FirstChildElement();
	if (save) {
		XMLNode* heroes = save->FirstChildElement("heroes");
		if (heroes) {
			XMLNode* hero = heroes->FirstChildElement("hero");
			while (hero) {
				// init heroes
				ObjectManager* objManer = ObjectManager::getInstance();

				std::string templ = hero->Attribute("template");
				CharInfo temp = objManer->getCharacterTemplate(templ);

				int health = atoi(hero->Attribute("health"));
				temp.health = health;

				int speed = atoi(hero->Attribute("speed"));
				temp.speed = speed;

				int damage = atoi(hero->Attribute("damage"));
				temp.damage = damage;

				int level = atoi(hero->Attribute("level"));
				temp.level = level;

				int experience = atoi(hero->Attribute("experience"));
				temp.experience = experience;

				_heroes.push_back(temp);
				
				hero = hero->NextSiblingElement("hero");
			}
		}
		XMLNode* artifacts = save->FirstChildElement("artifacts");
		if (artifacts) {
			XMLNode* artifact = artifacts->FirstChildElement("artifact");
			while (artifact) {
				// init artifacts
				std::string id = artifact->Attribute("id");
				_artifacts.push_back(id);
				artifact = artifact->NextSiblingElement("artifact");
			}
		}
		XMLNode* resources = save->FirstChildElement("resources");
		if (resources) {
			// init res
			_totalTime = atoi(resources->Attribute("total_time"));
			_gold = atoi(resources->Attribute("gold"));
			_provision = atoi(resources->Attribute("provision"));
		}
		XMLNode* level = save->FirstChildElement("level");
		if (level) {
			// init level
			_level = level->Attribute("file");
			_curAct = atoi(level->Attribute("act_id"));
		}

	}

	return true;
}