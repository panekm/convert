/*
The MIT License

Copyright (c) 2015 Maciej Panek

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
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
