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

Trans�ondition* Trans�ondition::create() {
	Trans�ondition* ret = new (std::nothrow) Trans�ondition();
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

Role* Role::create() {
	Role* ret = new (std::nothrow) Role();
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
		// ���������� �������� ����� �����
		XMLNode* eMap = eLvl->FirstChildElement("map");
		if (eMap) {
			_mapFile = eMap->Attribute("source");
		}
		// ������������ ����
		XMLNode* eActors = eLvl->FirstChildElement("actors");
		if (eActors) {
			XMLNode* eActor = eActors->FirstChildElement("actor");
			while (eActor) {
				std::string actorId = eActor->Attribute("id");
				Role* tempRole = Role::create();
				// ��������� ��������� � ���������
				XMLNode* eBehavior = eActor->FirstChildElement("behavior");
				while (eBehavior) {
					int actId = atoi(eBehavior->Attribute("act_id"));

					Behavior* behav = Behavior::create();

					std::string objectsSource = source + "/objects.xml";
					XMLDoc objDoc;
					objDoc.LoadFile(objectsSource.c_str());
					std::string tempId = eBehavior->Attribute("template");
					ObjectInfo* objInfo = ObjectInfo::create(objDoc, tempId);
					behav->baseObject = objInfo;

					std::string name = eBehavior->Attribute("name");
					behav->name = name;

					std::string team = eBehavior->Attribute("team");
					if (team == "friend") {
						behav->team = FRIEND;
					}
					else if (team == "enemy") {
						behav->team = ENEMY;
					}
					else if (team == "neutral") {
						behav->team = NEUTRAL;
					}

					tempRole->addBehavior(actId, behav);

					eBehavior = eBehavior->NextSiblingElement("behavior");
				}
				_actors.insert(actorId, tempRole);
				eActor = eActor->NextSiblingElement();
			}
		}
		// ���������� ���������� � ������
		XMLNode* eQuest = eLvl->FirstChildElement("quest");
		if (eQuest) {
			// ��������� �� �����
			XMLNode* eAct = eQuest->FirstChildElement("act");
			while (eAct) {
				int actId = atoi(eAct->Attribute("id"));
				Act* tempAct = Act::create();

				XMLNode* eTrans = eAct->FirstChildElement("transition");
				while (eTrans) {
					Trans�ondition* tempTrans = Trans�ondition::create();
					// ��������� ����� �����
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
							else if (name == "defeat") {
								Defeat* def = Defeat::create();
								def->target = eTask->Attribute("target");
								tempTrans->tasks.push_back(def);
							}

							eTask = eTask->NextSiblingElement();
						}

					}
					// ������ ��������� ���
					XMLNode* eNext = eTrans->FirstChildElement("next");
					if (eNext) {
						int nextId = eNext->IntAttribute("id");
						bool bFinal = eNext->BoolAttribute("final");
						tempTrans->next = nextId;
						tempTrans->final = bFinal;
					}

					tempAct->trans.push_back(tempTrans);
					eTrans = eTrans->NextSiblingElement("transition");
				}

				_quest.insert(actId, tempAct);
				eAct = eAct->NextSiblingElement("act");
			}
			// ������� � ����������� �� ������
			XMLNode* eReward = eQuest->FirstChildElement("reward");
			while (eReward) {
				int finalId = atoi(eReward->Attribute("id"));
				Reward* tempRew = Reward::create();

				XMLNode* eAdd = eReward->FirstChildElement();
				while (eAdd) {
					std::string name = eAdd->Name();

					if (name == "resources") {
						tempRew->gold = atoi(eAdd->Attribute("gold"));
						tempRew->provision = atoi(eAdd->Attribute("provision"));
						tempRew->experience = atoi(eAdd->Attribute("experience"));
					}
					else if (name == "artifact") {
						std::string id = eAdd->Attribute("id");
						tempRew->artifacts.push_back(id);
					}

					eAdd = eAdd->NextSiblingElement();
				}

				_rewards.insert(finalId, tempRew);
				eReward = eReward->NextSiblingElement("reward");
			}

		}

	}

	return true;
}
