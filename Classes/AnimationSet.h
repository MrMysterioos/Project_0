#pragma once
#include "cocos2d.h"

USING_NS_CC;

/**
 * @brief Класс, лежащий в основе большинства отображаемых объектов и содержащий набор анимаций
 *
 * AnimationSet класс, для быстрого обращения к анимациям конкретного объекта.
 * Объекты данного класса содержатся почти во всех визуальных элементах игровой сцены.
 * Классы Character, Container, Campfire являются адаптерами для AnimationSet.
 */
class AnimationSet : public Ref {
public:
	/**
	 * @brief Создать AnimationSet по данным из файла
	 * @param file Относительный путь до файла с параметрами
	 *
	 */
	static AnimationSet* create(std::string file);

	bool init();

	/**
	 * @brief Инициализирует AnimationSet по данным из файла
	 * @param file Относительный путь до файла с параметрами
	 *
	 */
	bool initWithFile(std::string file);

	/**
	 * @brief Метод, возвращающий уакзатель на Animation по его ключу
	 * @param Ключ для получения анимации
	 * @return Уакзатель на Animation
	 *
	 * getAnimation - метод, возвращающий уакзатель на Animation по его ключу.
	 * В большинстве случаем клучи анимаций объектов одного класса одинаковы.
	 * Например, у объекта класса Character должны быть такие поля как: Idle, Walk, Run и так далее.
	 */
	inline Animation* getAnimation(std::string key) {
		return _animations.at(key);
	}

	CREATE_FUNC(AnimationSet);
private:
	Map<std::string, Animation*> _animations;
};
