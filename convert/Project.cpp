/*
* Project.cpp
*
*  Created on: Jul 14, 2015
*      Author: mpanek
*/

#include "Project.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

#define MIL 0.0254f

Project::Project()
{
	// TODO Auto-generated constructor stub

}

Project::~Project()
{
	// TODO Auto-generated destructor stub
}

bool Project::SaveToFile(const std::string &fileName)
{
	std::cout << "Saving project to file: " << fileName << std::endl;

	std::fstream file(fileName, std::ios::out);

	file << "{ SMF - NEXT_INFO - PART }" << std::endl;
	file << "Standard.sml;" << std::endl; //lib1
	file << ";" << std::endl; //lib2
	file << ";" << std::endl; //lib3
	file << "VERSION 101;" << std::endl; //version
	file << "PRISME CONVERT;" << std::endl; //origin
	file << "PANEK;" << std::endl; //operator
	file << "19.02.1990;" << std::endl; //date
	file << "21.15;" << std::endl; //time
	file << "Y;" << std::endl; //nozzle optimization
	file << "Y;" << std::endl; //feeder optimization
	file << "0.0254;" << std::endl; //grid
	file << "0;" << std::endl; //pcb turning angle
	file << "N;" << std::endl; //pcb mirroring

	file << m_thickness << ";" << std::endl; //pcb thickness
	file << m_width << ";" << std::endl; //pcb width(x)
	file << m_height << ";" << std::endl; //pcb height(y)

	file << "0.0;" << std::endl; //zero point x
	file << "0.0;" << std::endl; //zero point y

	file << "0.0;" << std::endl; //pcb distance x
	file << "0.0;" << std::endl; //pcb distance y

	file << "1;" << std::endl; //pcb amount x
	file << "1;" << std::endl; //pcb amount y

	file << m_components.size() << ";" << std::endl; //component count
	file << m_feeders.size() << ";" << std::endl; //feeder count

	file << "322;" << std::endl; //version
	file << "{ SMF - NEXT_INFO - PART }" << std::endl;

	for (auto component : m_components)
	{
		//save component to file
		component->SaveToFile(file);
	}

	file << "{ SMF - NEXT_INFO - PART }" << std::endl;

	for (auto feeder : m_feeders)
	{
		//save feeder to file
		feeder->SaveToFile(file);
	}


	file << "{ SMF - NEXT_INFO - PART }" << std::endl;
	file << "0;" << std::endl; //pcb skipping: one pcb - only one value

	file << "{ SMF - NEXT_INFO - PART }" << std::endl;
	file << "3,0.4,+,0,+,0;" << std::endl; //dispenser
	file << "{ SMF - NEXT_INFO - PART }" << std::endl;
	file << "N;" << std::endl; //generating dispenser file
	file << "{ SMF - NEXT_INFO - PART }" << std::endl;
	file << "300,20,30.7,15.5,8,5;" << std::endl; //tableau

	file.close();

	std::cout << "Done" << std::endl;

	return true;
}

Feeder *Project::AddFeederForComponent(Component *comp)
{
	Feeder *feeder = new Feeder(m_feeders.size() + 1, comp);

	m_feeders.push_back(feeder);
	return feeder;
}

int Project::FindFeederIDByComponent(Component *comp)
{
	int ret = 1;
	for (auto feeder : m_feeders)
	{
		if (feeder->ComponentMatches(comp))
		{
			return ret;
		}
		ret++;
	}

	return -1;
}

Feeder *Project::FindFeederByComponent(Component *comp)
{
	for (auto feeder : m_feeders)
	{
		if (feeder->ComponentMatches(comp))
		{
			return feeder;
		}
	}

	return nullptr;
}

CSVRow Project::CSVParseLine(std::istream &file)
{
	CSVRow ret;
	std::string line;
	std::getline(file, line);

	std::stringstream ss(line);
	std::string col;

	while (std::getline(ss, col, ','))
	{
		std::string col2;
		while (std::count(col.begin(), col.end(), '"') % 2 != 0 && std::getline(ss, col2, ','))
		{
			//we are in the middle of column
			col += '/'; //replace comma with slash, as Place_it won't accept commas in values
			col += col2;
		}
		//remove all quotation marks
		col.erase(std::remove(col.begin(), col.end(), '"'), col.end());
		ret.push_back(col);
		//	std::cout << "Added column: " << col << std::endl;
	}

	return ret;
}

int Project::CSVFindColIndex(CSVRow &CSVLine, std::string colName)
{
	int index = 0;
	for (auto s : CSVLine)
	{
		if (s.compare(colName) == 0)
		{
			return index;
		}
		index++;
	}
	return -1;
}

float Project::ParsePosition(std::string &pos)
{
	size_t index = pos.find("mm");
	if (index != std::string::npos)
	{
		pos.resize(index);
		return std::stof(pos);
	}
	index = pos.find("mil");
	if (index != std::string::npos)
	{
		return std::stof(pos) * MIL;
	}
	return 0.0f;
}

bool Project::LoadCSV(const std::string &fileName)
{
	std::cout << "Trying to load project from file " << fileName << std::endl;

	std::ifstream file(fileName);
	CSVRow header = CSVParseLine(file);
	int line = 1;

	int designatorCol = CSVFindColIndex(header, "Designator");
	int footprintCol = CSVFindColIndex(header, "Footprint");
	int midXCol = CSVFindColIndex(header, "Mid X");
	int midYCol = CSVFindColIndex(header, "Mid Y");
	int layerCol = CSVFindColIndex(header, "Layer");
	int rotCol = CSVFindColIndex(header, "Rotation");
	int valueCol = CSVFindColIndex(header, "Comment");

	if (designatorCol == -1 || footprintCol == -1 || midXCol == -1
		|| midYCol == -1 || layerCol == -1 || rotCol == -1
		|| valueCol == -1)
	{
		std::cout << "Error parsing CSV header. Column not found" << std::endl;
		file.close();
		return false;
	}

	//Designator Footprint Mid X Mid Y
	//Ref X Ref Y Pad X  Pad Y TB Rotation Comment

	while (file.eof() == false)
	{
		line++;
		CSVRow row = CSVParseLine(file);
		if (row.size() != header.size())
		{
			std::cout << "Skipping line: " << line << std::endl;
			continue;
		}

		Component *comp = new Component();

		comp->SetDesignator(row[designatorCol]);
		comp->SetFootprint(row[footprintCol]);
		comp->SetValue(row[valueCol]);
		comp->SetMidX(ParsePosition(row[midXCol]));
		comp->SetMidY(ParsePosition(row[midYCol]));
		comp->SetRotation(std::stof(row[rotCol]));

		Feeder *feeder = FindFeederByComponent(comp);

		if (feeder == nullptr)
		{
			feeder = AddFeederForComponent(comp);
		}

		comp->SetFeeder(feeder);

		m_components.push_back(comp);
	}

	file.close();

	std::cout << "Done" << std::endl;

	return true;
}
