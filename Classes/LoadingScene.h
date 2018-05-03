#pragma once

#include "cocos2d.h"
#include "ui\CocosGUI.h"

USING_NS_CC;
using namespace ui;
/**
 * @brief Сцена, запускаемая перед игрой
 *
 * Данная сцена запускатся перед основной игрой, во врепя пока она отображается происходит загрузка ресурсов.
 */
class LoadingScene : public Scene {
public:

	/**
	 * @brief Метод для создания сцены
	 *
	 */
	static LoadingScene* createScene();

	/**
	 * @brief Метод инициализации LoagingScene
	 *
	 */
	virtual bool init() override;

	virtual void update(float dt) override;

	CREATE_FUNC(LoadingScene);

private:
	LoadingBar* _loadingBar;

};