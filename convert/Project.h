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

#ifndef PROJECT_H_
#define PROJECT_H_

#include <string>
#include <list>
#include <vector>

#include "Feeder.h"
#include "Component.h"

typedef std::vector<std::string> CSVRow;

class Project
{
public:
	Project();
	virtual ~Project();

	bool SaveToFile(const std::string &fileName);
	bool LoadCSV(const std::string &fileName);
private:
	float m_width = 370.0f;
	float m_height = 240.0f;
	float m_thickness = 1.6f;

	float ParsePosition(std::string &pos);
	Feeder *AddFeederForComponent(Component *comp);
	Feeder *FindFeederByComponent(Component *comp);
	CSVRow CSVParseLine(std::istream &file);
	int CSVFindColIndex(CSVRow &CSVLine, std::string colName);

	std::list<Component *> m_components;
	std::list<Feeder *> m_feeders;
};

#endif /* PROJECT_H_ */
