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
