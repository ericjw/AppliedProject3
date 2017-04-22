#ifndef _PARSE_H
#define _PARSE_H

#include <iostream>
#include <fstream>
#include <QJsonDocument>
#include "sceneobjects.hpp"

class JSONParse {
public:
	//take in a file name, read into a QJsonDocument, 
	//and store values in the scene
	JSONParse(std::string fname);

	void parse();


private:
	QJsonDocument jdoc;
	std::vector<Sphere> spheres;
	std::vector<Light> lights;
	std::vector<Plane> planes;
	//Camera cam;

};

#endif // !_PARSE_H
