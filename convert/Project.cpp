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

	for(auto component : m_components)
	{
		//save component to file
		component->SaveToFile(file);
	}

	file << "{ SMF - NEXT_INFO - PART }" << std::endl;

	for(auto feeder : m_feeders)
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
	for(auto feeder : m_feeders)
	{
		if(feeder->ComponentMatches(comp))
		{
			return ret;
		}
		ret++;
	}

	return -1;
}

Feeder *Project::FindFeederByComponent(Component *comp)
{
	for(auto feeder : m_feeders)
	{
		if(feeder->ComponentMatches(comp))
		{
			return feeder;
		}
	}

	return nullptr;
}

float Project::ParsePosition(std::string &pos)
{
	return 0.0f;
}

//really primitive parser
bool Project::LoadAltium(const std::string &fileName)
{
    std::fstream file(fileName);
    std::string line;
    std::vector<std::string> header;

    getline(file, line);
    getline(file, line);

    //Designator Footprint Mid X Mid Y
    //Ref X Ref Y Pad X  Pad Y TB Rotation Comment

    while(getline(file, line))
    {
    	if(!line.length())
    	{
    		continue;
    	}

    	std::stringstream ss(line);
    	unsigned int col = 0;

		Component *comp = new Component();

    	while(true)
    	{
    		std::string temp;
    		ss >> temp;
    		if(temp.length() == 0 || col >= header.size())
    		{
    			break;
    		}

    		if(header[col].compare("Designator") == 0)
    		{
    	//		comp->designator = temp;
    		}
    		else if(header[col].compare("Mid X") == 0)
    		{
    	//		comp->mid_x = ParsePosition(temp);
    		}
    		else if(header[col].compare("Mid Y") == 0)
    		{
    	//		comp->mid_y = ParsePosition(temp);
    		}
    		else if(header[col].compare("Comment") == 0) //value
    		{
    	//		comp->value = temp;
    		}

    		col++;
    	}

    	Feeder *feeder = FindFeederByComponent(comp);

    	if(feeder == nullptr)
    	{
			feeder = AddFeederForComponent(comp);
    	}

    	comp->SetFeeder(feeder);
    }

	return true;
}

void Project::Random(int count)
{
	for (int i = 0; i < count; i++)
	{
		Component *comp = new Component();
		comp->SetDesignator("C" + std::to_string(i));
		comp->SetFootprint(std::string("1206"));
		comp->SetValue(std::to_string(rand() % 5) + "N");
		comp->SetMidX((rand() % 1500) / 8.0f);
		comp->SetMidY((rand() % 1500) / 8.0f);
		comp->SetRotation(rand() % 359);
		Feeder *feeder = FindFeederByComponent(comp);

		if (feeder == nullptr)
		{
			feeder = AddFeederForComponent(comp);
		}

		comp->SetFeeder(feeder);
		m_components.push_back(comp);
	}
}
