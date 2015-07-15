/*
* main.cpp
*
*  Created on: May 21, 2015
*      Author: mpanek
*/

#include "Project.h"

#include <iostream>
#include <string>
#include <algorithm>

int main(int argc, char *argv[])
{
	std::cout << "Convert 1.0a" << std::endl;

	if (argc < 2)
	{
		std::cout << "Usage: " << argv[0] 
			<< " input_file [output_file]" << std::endl;
		return -1;
	}

	Project project;

	if (project.LoadCSV(argv[1]) == false)
	{
		std::cout << "Error loading " << argv[1] 
			<< ". Quiting." << std::endl;
		return -1;
	}
	
	
	std::string outputFileName;
	if (argc < 3)
	{
		outputFileName = argv[1];
		size_t index = outputFileName.find_last_of('.');
		if (index != std::string::npos)
		{
			outputFileName.resize(index);
		}
		outputFileName += ".smf";
	}
	else
	{
		outputFileName = argv[2];
	}

	if (project.SaveToFile(outputFileName) == false)
	{
		std::cout << "Error saving project into: " 
			<< outputFileName << std::endl;
		return -1;
	}

	return 0;
}
