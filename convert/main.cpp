/*
 * main.cpp
 *
 *  Created on: May 21, 2015
 *      Author: mpanek
 */

#include "Project.h"

#include <iostream>

#define MIL 0.0254

int main(int argc, char *argv[])
{
	std::cout << "Convert 1.0a" << std::endl;
	Project project;
	project.Random(100);

	project.SaveToFile("proj.smf");
}



