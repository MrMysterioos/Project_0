#pragma once

#include "cocos2d.h"
#include "tinyxml2\tinyxml2.h"

USING_NS_CC;

/**
 * @brief Класс для хранения различной информации об игровых сущностях
 *
 * Класс ObjectInfo представляет собой таблицу значений, которая может хранить в себе
 * информацию об игровых объектах, задачах и других подобных сущностях.
 * ObjectInfo часто используется в качестве аргумента при создании объектов.
 */
class ObjectInfo {
public:

	/**
	 * @brief Конструктор для ObjectInfo
	 *
	 */
	ObjectInfo();

	/**
	 * @brief Метод, инициализирующий ObjectInfo из XML элемента
	 * @param [in] node Указатель на элемент документа
	 */
	bool initWithXmlElement(tinyxml2::XMLElement* node);

	/**
	* @brief Метод, инициализирующий ObjectInfo из XML документа по его id
	* @param [in] doc Путь до документа
	* @param [in] id Id элемента описанного в файле
	*/
	bool initWithElementId(std::string doc, std::string id);

	/**
	 * @brief Получить тег типа
	 *
	 */
	inline std::string getTypeName() { return _typeName; }

	/**
	 * @brief Получить атрибут по его ключу
	 *
	 */
	inline std::string getAttribute(std::string key) { return _info.at(key); }

	/**
	 * @brief Метод, проверяющий, был ли инициализирован объект
	 * @return true - если объект иницализирован
	 */
	inline bool isInit() { return _bInit; }

private:
	std::string _typeName;
	std::map<std::string, std::string> _info;
	bool _bInit;

};

