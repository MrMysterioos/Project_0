#include "LevelInfo.h"
#include "ObjectManager.h"
#include "tinyxml2\tinyxml2.h"

USING_NS_CC;

Talk* Talk::create() {
	Talk* ret = new (std::nothrow) Talk();
	ret->autorelease();
	return ret;
}

Defeat* Defeat::create() {
	Defeat* ret = new (std::nothrow) Defeat();
	ret->autorelease();
	return ret;
}

TransÑondition* TransÑondition::create() {
	TransÑondition* ret = new (std::nothrow) TransÑondition();
	ret->autorelease();
	return ret;
}

Act* Act::create() {
	Act* ret = new (std::nothrow) Act();
	ret->autorelease();
	return ret;
}

Reward* Reward::create() {
	Reward* ret = new (std::nothrow) Reward();
	ret->autorelease();
	return ret;
}

LevelInfo*  LevelInfo::create(std::string file) {
	LevelInfo* ret = new (std::nothrow) LevelInfo();
	if (ret->initWithFile(file)) {
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
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
		// çàïîìèíàåì íàçâàíèå ôàéëà êàðòû
		XMLNode* eMap = eLvl->FirstChildElement("map");
		if (eMap) {
			_mapFile = eMap->Attribute("file");
		}
		// ðàñïðåäåëÿåì ðîëè
		XMLNode* eActors = eLvl->FirstChildElement("actors");
		if (eActors) {
			XMLNode* eActor = eActors->FirstChildElement("actor");
			while (eActor) {
				std::string actorId = eActor->Attribute("id");
				std::map<int, std::shared_ptr<ObjectInfo>> tempRole;
				// ñ÷èòûâàåì èçìåíåíèÿ â ïîâåäåíèè
				XMLNode* eBehavior = eActor->FirstChildElement("behavior");
				if (eBehavior) {
					int actId = atoi(eBehavior->Attribute("act_id"));

					XMLNode* eObjInf = eBehavior->FirstChildElement();
					if (eObjInf) {

						std::string name = eObjInf->Name();

						if (name == "character") {
							std::string charTemp = eObjInf->Attribute("template");
							std::shared_ptr<CharInfo> charInf = std::make_shared<CharInfo>();
							charInf->name = eObjInf->Attribute("name");
							charInf->team = eObjInf->Attribute("team");
							tempRole.insert(std::pair<int, std::shared_ptr<ObjectInfo>>(actId, charInf));
						}
						else if (name == "container") {
							std::string contTemp = eObjInf->Attribute("template");
							std::shared_ptr<ContInfo> contInf = std::make_shared<ContInfo>();
							contInf->name = eObjInf->Attribute("name");
							tempRole.insert(std::pair<int, std::shared_ptr<ObjectInfo>>(actId, contInf));
						}
						else if (name == "campfire") {
							std::string fireTemp = eObjInf->Attribute("template");
							std::shared_ptr<FireInfo> fireInf = std::make_shared<FireInfo>();
							fireInf->name = eObjInf->Attribute("name");
							tempRole.insert(std::pair<int, std::shared_ptr<ObjectInfo>>(actId, fireInf));
						}

					}

				}
				_actors.insert(std::pair<std::string, std::map<int, std::shared_ptr<ObjectInfo>>>(actorId, tempRole));
				eActor = eActor->NextSiblingElement();
			}
		}
		// çàïèñûâàåì èíôîðìàöèþ î êâåñòå
		XMLNode* eQuest = eLvl->FirstChildElement("quest");
		if (eQuest) {
			// èíôîðìàöè îá àêòàõ
			XMLNode* eAct = eQuest->FirstChildElement("act");
			while (eAct) {
				int actId = atoi(eAct->Attribute("id"));
				Act tempAct;

				XMLNode* eTrans = eAct->FirstChildElement("transition");
				while (eTrans) {
					TransÑondition* tempTrans = TransÑondition::create();

					XMLNode* eTasks = eTrans->FirstChildElement("tasks");
					if (eTasks) {

						XMLNode* eTask = eTasks->FirstChildElement();
						while (eTask) {
							std::string name = eTask->Name();

							if (name == "talk") {
								Talk* talk = Talk::create();
								talk->target = eTask->Attribute("target");
								talk->dialogFile = eTask->Attribute("file");
								talk->result = atoi(eTask->Attribute("result"));
								tempTrans->tasks.push_back(talk);
							}

							if (name == "defeat") {
								Defeat* def = Defeat::create();
								def->target = eTask->Attribute("target");
								tempTrans->tasks.push_back(def);
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
			// íàãðàäû â çàâèñèìîñòè îò ôèíàëà
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
