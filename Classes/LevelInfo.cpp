#include "LevelInfo.h"
#include "ObjectManager.h"
#include "tinyxml2\tinyxml2.h"

USING_NS_CC;

ObjectInfo getObjectInfo(tinyxml2::XMLDocument& objDoc, std::string id);

LevelInfo*  LevelInfo::create(std::string file) {
	LevelInfo* ret = new (std::nothrow) LevelInfo();
	if (ret->initWithFile(file)) {
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool LevelInfo::initWithFile(std::string source) {
	typedef tinyxml2::XMLDocument XMLDoc;
	typedef tinyxml2::XMLElement XMLNode;

	std::string levelSource = source + "/level.xml";

	XMLDoc doc;
	doc.LoadFile(levelSource.c_str());
	if (doc.Error()) {
		return false;
	}

	XMLNode* eLvl = doc.FirstChildElement("Level");
	if (eLvl) {
		// запоминаем название файла карты
		XMLNode* eMap = eLvl->FirstChildElement("map");
		if (eMap) {
			_mapFile = eMap->Attribute("source");
		}
		else
			return false;
		// распределяем роли
		XMLNode* eActors = eLvl->FirstChildElement("actors");
		if (eActors) {
			XMLNode* eActor = eActors->FirstChildElement("actor");
			while (eActor) {
				// создаем актера
				std::string actorId = eActor->Attribute("id");
				std::string actorTemplate = eActor->Attribute("template");

				std::string objectsSource = source + "/objects.xml";
				XMLDoc objDoc;
				objDoc.LoadFile(objectsSource.c_str());
				if (objDoc.Error())
					return false;
				ObjectInfo objInf = getObjectInfo(objDoc, actorTemplate);

				Role tempRole;
				tempRole.objInf = objInf;
				// считываем изменения в поведении
				XMLNode* eBehavior = eActor->FirstChildElement("behavior");
				while (eBehavior) {
					int actId = atoi(eBehavior->Attribute("act_id"));

					Behavior behav;

					std::string name = eBehavior->Attribute("name");
					behav.name = name;

					std::string team = eBehavior->Attribute("team");
					if (team == "friend") {
						behav.team = FRIEND;
					}
					else if (team == "enemy") {
						behav.team = ENEMY;
					}
					else if (team == "neutral") {
						behav.team = NEUTRAL;
					}

					tempRole.addBehavior(actId, behav);

					eBehavior = eBehavior->NextSiblingElement("behavior");
				}
				_actors.insert(std::pair<std::string, Role>(actorId, tempRole));
				eActor = eActor->NextSiblingElement();
			}
		}
		else
			return false;
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
					Transition tempTrans;
					// загружаем спиок задач
					XMLNode* eTasks = eTrans->FirstChildElement("tasks");
					if (eTasks) {

						XMLNode* eTask = eTasks->FirstChildElement();
						while (eTask) {
							ObjectInfo taskInf;
							taskInf.initWithXmlElement(eTask);
							tempTrans.tasks.push_back(taskInf);

							eTask = eTask->NextSiblingElement();
						}

					}
					else
						return false;
					// задаем следующий акт
					XMLNode* eNext = eTrans->FirstChildElement("next");
					if (eNext) {
						int nextId = eNext->IntAttribute("id");
						bool bFinal = eNext->BoolAttribute("final");
						tempTrans.next = nextId;
						tempTrans.final = bFinal;
					}
					else
						return false;
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
				tempRew.gold = 0;
				tempRew.provision = 0;
				tempRew.experience = 0;

				XMLNode* eAdd = eReward->FirstChildElement();
				while (eAdd) {
					std::string name = eAdd->Name();

					if (name == "resources") {
						tempRew.gold += eAdd->IntAttribute("gold");
						tempRew.provision += eAdd->IntAttribute("provision");
						tempRew.experience += eAdd->IntAttribute("experience");
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
		else
			return false;

	}
	else
		return false;

	return true;
}

ObjectInfo getObjectInfo(tinyxml2::XMLDocument& objDoc, std::string id) {
	typedef tinyxml2::XMLDocument XMLDoc;
	typedef tinyxml2::XMLElement XMLNode;

	ObjectInfo objInf;

	XMLNode* eRoot = objDoc.FirstChildElement();
	if (eRoot) {
		XMLNode* e = eRoot->FirstChildElement();
		while (e) {
			std::string otherId = e->Attribute("id");
			if (otherId == id) {
				objInf.initWithXmlElement(e);
				return objInf;
			}

			e = e->NextSiblingElement();
		}
	}
	return objInf;
}