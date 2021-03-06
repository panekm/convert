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
