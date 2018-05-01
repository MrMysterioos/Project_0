#pragma once

#include "cocos2d.h"
#include "tinyxml2\tinyxml2.h"

USING_NS_CC;

/**
 * @brief ����� ��� �������� ��������� ���������� �� ������� ���������
 *
 * ����� ObjectInfo ������������ ����� ������� ��������, ������� ����� ������� � ����
 * ���������� �� ������� ��������, ������� � ������ �������� ���������.
 * ObjectInfo ����� ������������ � �������� ��������� ��� �������� ��������.
 */
class ObjectInfo {
public:

	/**
	 * @brief ����������� ��� ObjectInfo
	 *
	 */
	ObjectInfo();

	/**
	 * @brief �����, ���������������� ObjectInfo �� XML ��������
	 * @param [in] node ��������� �� ������� ���������
	 */
	bool initWithXmlElement(tinyxml2::XMLElement* node);

	/**
	 * @brief �������� ��� ����
	 *
	 */
	inline std::string getTypeName() { return _typeName; }

	/**
	 * @brief �������� ������� �� ��� �����
	 *
	 */
	inline std::string getAttribute(std::string key) { return _info.at(key); }

	/**
	 * @brief �����, �����������, ��� �� ��������������� ������
	 * @return true - ���� ������ ��������������
	 */
	inline bool isInit() { return _bInit; }

private:
	std::string _typeName;
	std::map<std::string, std::string> _info;
	bool _bInit;

};

