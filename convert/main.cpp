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
