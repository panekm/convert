/*
 * Component.h
 *
 *  Created on: Jul 14, 2015
 *      Author: mpanek
 */

#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <fstream>
#include <string>

class Feeder;

class Component
{
public:
	Component();
	virtual ~Component();
	void SaveToFile(std::fstream &file);

	void SetFeeder(Feeder *feeder);

	inline void SetDesignator(std::string &designator) { m_designator = designator; }
	inline void SetFootprint(std::string &footprint) { m_footprint = footprint; }

	inline void SetMidX(float midX) { m_midX = midX; }
	inline void SetMidY(float midY) { m_midY = midY; }
	inline void SetRotation(float rotation) { m_rotation = rotation; };
	inline void SetValue(std::string &value) { m_value = value; };

	inline std::string &GetDesignator() { return m_designator; }
	inline std::string &GetFootprint() { return m_footprint; }
	inline std::string &GetValue() { return m_value; }
private:
	std::string m_designator;
	std::string m_footprint;
	float m_midX;
	float m_midY;
	float m_rotation;
	std::string m_value;
	Feeder *m_feeder;
};

#endif /* COMPONENT_H_ */
