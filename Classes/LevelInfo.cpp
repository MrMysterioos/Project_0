#include "LevelInfo.h"
#include "ObjectManager.h"
#include "tinyxml2\tinyxml2.h"

USING_NS_CC;

LevelInfo::LevelInfo(std::string file) {
	initWithFile(file);
}

bool LevelInfo::initWithFile(std::string file) {
	typedef tinyxml2::XMLDocument XMLDoc;
	typedef tinyxml2::XMLElement XMLNode;

	std::string path = "levels/" + file;

	XMLDoc doc;
	doc.LoadFile(path.c_str());
	if (doc.Error()) {
		return false;
	}

	XMLNode* eLvl = doc.FirstChildElement("Level");
	if (eLvl) {
		// запоминаем название файла карты
		XMLNode* eMap = eLvl->FirstChildElement("map");
		if (eMap) {
			_mapFile = eMap->Attribute("file");
		}
		// распредел€ем роли
		XMLNode* eActors = eLvl->FirstChildElement("actors");
		if (eActors) {
			XMLNode* eActor = eActors->FirstChildElement("actor");
			while (eActor) {
				std::string actorId = eActor->Attribute("id");
				Role tempRole;
				// считываем стандартное поведение
				XMLNode* eDefault = eActor->FirstChildElement("default");
				if (eDefault) {

					XMLNode* eObjInf = eDefault->FirstChildElement();
					if (eObjInf) {

						std::string name = eObjInf->Name();

						if (name == "character") {
							std::string charTemp = eObjInf->Attribute("template");
							CharInfo charInf = ObjectManager::getInstance()->getCharacterTemplate(charTemp);
							charInf.name = eObjInf->Attribute("name");
							charInf.team = eObjInf->Attribute("team");
							tempRole.default = charInf;
						}
						else if (name == "container") {
							std::string contTemp = eObjInf->Attribute("template");
							ContInfo contInf = ObjectManager::getInstance()->getContainerTemplate(contTemp);
							contInf.name = eObjInf->Attribute("name");
							tempRole.default = contInf;
						}
						else if (name == "campfire") {
							std::string fireTemp = eObjInf->Attribute("template");
							FireInfo fireInf = ObjectManager::getInstance()->getCampfireTemplate(fireTemp);
							fireInf.name = eObjInf->Attribute("name");
							tempRole.default = fireInf;
						}

					}

				}
				// считываем изменени€ в поведении
				XMLNode* eChange = eActor->FirstChildElement("change");
				if (eChange) {
					int actId = atoi(eChange->Attribute("act_id"));

					XMLNode* eObjInf = eChange->FirstChildElement();
					if (eObjInf) {

						std::string name = eObjInf->Name();

						if (name == "character") {
							std::string charTemp = eObjInf->Attribute("template");
							CharInfo charInf = ObjectManager::getInstance()->getCharacterTemplate(charTemp);
							charInf.name = eObjInf->Attribute("name");
							charInf.team = eObjInf->Attribute("team");
							tempRole.changes.insert(std::pair<int, CharInfo>(actId, charInf));
						}
						else if (name == "container") {
							std::string contTemp = eObjInf->Attribute("template");
							ContInfo contInf = ObjectManager::getInstance()->getContainerTemplate(contTemp);
							contInf.name = eObjInf->Attribute("name");
							tempRole.changes.insert(std::pair<int, ContInfo>(actId, contInf));
						}
						else if (name == "campfire") {
							std::string fireTemp = eObjInf->Attribute("template");
							FireInfo fireInf = ObjectManager::getInstance()->getCampfireTemplate(fireTemp);
							fireInf.name = eObjInf->Attribute("name");
							tempRole.changes.insert(std::pair<int, FireInfo>(actId, fireInf));
						}

					}

				}
				// !!!”Ѕ–ј“№ ѕќ¬“ќ–яёў»…—я  ќƒ!!! (если это возможно)
				_actors.insert(std::pair<std::string, Role>(actorId, tempRole));
				eActor = eActor->NextSiblingElement();
			}
		}
		// записываем информацию о квесте
		XMLNode* eQuest = eLvl->FirstChildElement("quest");
		if (eQuest) {
			// информаци об актах
			XMLNode* eAct = eQuest->FirstChildElement("act");
			while (eAct) {
				int actId = atoi(eAct->Attribute("id"));
				Act tempAct;

				XMLNode* eTrans = eAct->FirstChildElement("transition");
				while (eTrans) {
					Trans—ondition tempTrans;

					XMLNode* eTasks = eTrans->FirstChildElement("tasks");
					if (eTasks) {

						XMLNode* eTask = eTasks->FirstChildElement();
						while (eTask) {
							std::string name = eTask->Name();

							if (name == "talk") {
								Talk talk;
								talk.target = eTask->Attribute("target");
								talk.dialogFile = eTask->Attribute("file");
								talk.result = atoi(eTask->Attribute("result"));
								tempTrans.tasks.push_back(talk);
							}

							if (name == "defeat") {
								Defeat def;
								def.target = eTask->Attribute("target");
								tempTrans.tasks.push_back(def);
							}

							eTask = eTask->NextSiblingElement();
						}

					}

					tempAct.trans.push_back(tempTrans);
					eTrans = eTrans->NextSiblingElement("transition");
				}

				_quest.insert(std::pair<int, Act>(actId, tempAct));
				eAct = eAct->NextSiblingElement("act");
			}
			// награды в зависимости от финала
			XMLNode* eReward = eQuest->FirstChildElement("reward");
			while (eReward) {
				int finalId = atoi(eReward->Attribute("id"));
				Reward tempRew;

				XMLNode* eAdd = eReward->FirstChildElement();
				while (eAdd) {
					std::string name = eAdd->Name();

					if (name == "resources") {
						tempRew.gold = atoi(eAdd->Attribute("gold"));
						tempRew.provision = atoi(eAdd->Attribute("provision"));
						tempRew.experience = atoi(eAdd->Attribute("experience"));
					}
					else if (name == "artifact") {
						std::string id = eAdd->Attribute("id");
						tempRew.artifacts.push_back(id);
					}

					eAdd = eAdd->NextSiblingElement();
				}

				_rewards.insert(std::pair<int, Reward>(finalId, tempRew));
				eReward = eReward->NextSiblingElement("reward");
			}

		}

	}

	return true;
}