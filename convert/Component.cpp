/*
 * Component.cpp
 *
 *  Created on: Jul 14, 2015
 *      Author: mpanek
 */

#include "Component.h"
#include "Feeder.h"

#include <iostream>

Component::Component()
{
	// TODO Auto-generated constructor stub

}

Component::~Component()
{
	// TODO Auto-generated destructor stub
}

/*
 * C1 - connection diagram indentification
 * CONDENSATOR - component-type
 * 100NF - component value
 * 1206 - case-type
 * 10 - tolerance
 * 65V - identification value
 * 1 - waste box
 * 1234567 - additional info
 * 30.34 - X-coordinate in mm
 * 78.2 - Y coordinate in mm
 * 180 - R coordinate in degree
 * 0 - feeder type(0 or T?)
 * Y - to place or not to place
 * 4 - feeder number
 * 0 - reminder for feeder optimization??
 **/

void Component::SaveToFile(std::fstream &file)
{
	//R1,WIDERSTAND,100K,1206,5, ,1,1234567,20.24,56.78,180,0,Y,1,0;
	file << m_designator << ",";

	file << m_feeder->getComponentType() << ",";
	file << m_feeder->getValue() << ",";

	file << m_feeder->getFootprint() << ",";
	file << m_feeder->getTolerance() << ",";
	file << m_feeder->getIDValue() << ",";
	file << m_feeder->getWasteBox() << ",";
	file << m_feeder->getAdditionalInfo() << ",";

	file << m_midX << ",";
	file << m_midY << ",";
	file << m_rotation << ",";

	file << m_feeder->getType1() << ",";
	file << "Y,"; //place!
	file << m_feeder->getNumber() << ",";
	file << "0"; //?!?
	file << ";" << std::endl;
}

void Component::SetFeeder(Feeder *feeder)
{
	m_feeder = feeder;
	feeder->increaseUseCount();
}
