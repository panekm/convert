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

#include "Feeder.h"
#include "Component.h"

class Project
{
public:
	Project();
	virtual ~Project();

	bool SaveToFile(const std::string &fileName);
	bool LoadAltium(const std::string &fileName);

	void Random(int count);
private:
	float m_width = 370.0f;
	float m_height = 240.0f;
	float m_thickness = 1.6f;

	float ParsePosition(std::string &pos);
	Feeder *AddFeederForComponent(Component *comp);
	int FindFeederIDByComponent(Component *comp);
	Feeder *FindFeederByComponent(Component *comp);

	std::list<Component *> m_components;
	std::list<Feeder *> m_feeders;
};

#endif /* PROJECT_H_ */
