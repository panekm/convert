/*
 * Feeder.cpp
 *
 *  Created on: Jul 14, 2015
 *      Author: mpanek
 */

#include "Feeder.h"

Feeder::Feeder(int number, Component *comp): m_number(number)
{
	// TODO Auto-generated constructor stub
	m_footprint = std::string(comp->GetFootprint());
	m_value = std::string(comp->GetValue());
}

bool Feeder::ComponentMatches(Component *comp)
{
	if(m_value.compare(comp->GetValue()) != 0
			|| m_footprint.compare(comp->GetFootprint()) != 0)
	{
		return false;
	}
	return true;
}

/*
 * feeder type(0 or T)
 * feeder type ??!?!?!(1-3 ??)
 * component-type e.g. CONDENSATOR
 * component value e.g. 100NF
 * case-type e.g. 1206
 * toleracne e.g. 5
 * wastebox e.g. 1
 * nozzle 1-6
 * amount per PCB
 * feeder number (1-55 or T)
*/

void Feeder::SaveToFile(std::fstream &file)
{
	//0,1,WIDERSTAND,100K,1206,5,1,1,1,1;
	file << m_type1 << ",";
	file << m_type2 << ",";
	file << m_componentType << ",";
	file << m_value << ",";
	file << m_footprint << ",";
	file << m_tolerance << ",";
	file << m_wasteBox << ",";
	file << m_nozzle << ",";
	file << m_useCount << ",";
	file << m_number << ";" << std::endl;
}
