/*
* Project.h
*
*  Created on: Jul 14, 2015
*      Author: mpanek
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
