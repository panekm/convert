/*
 * Feeder.h
 *
 *  Created on: Jul 14, 2015
 *      Author: mpanek
 */

#ifndef FEEDER_H_
#define FEEDER_H_

#include <fstream>
#include <string>

#include "Component.h"

class Feeder
{
public:
	Feeder(int number, Component *comp);
	void SaveToFile(std::fstream &file);
	bool ComponentMatches(Component *comp);

	inline std::string &getComponentType() { return m_componentType; }
	inline std::string &getValue() { return m_value; }
	inline std::string &getFootprint() { return m_footprint; }
	inline std::string &getIDValue() { return m_idValue; }
	inline int getWasteBox() { return m_wasteBox; }
	inline std::string &getAdditionalInfo() { return m_additionalInfo; }
	inline std::string &getType1() { return m_type1; } //0 or T
	inline std::string &getType2() { return m_type2; } //1 - 3??
	inline int getTolerance() { return m_tolerance; }
	inline int getNumber() { return m_number; }

	inline void increaseUseCount() { m_useCount++; }
private:
	int m_number;
	std::string m_componentType = "SMD";
	std::string m_value;
	std::string m_footprint;
	int m_tolerance = 1;
	std::string m_idValue;
	int m_wasteBox = 1;
	int m_nozzle = 1;
	std::string m_additionalInfo;
	std::string m_type1 = "0";
	std::string m_type2 = "1";

	int m_useCount = 0;
};

#endif /* FEEDER_H_ */
