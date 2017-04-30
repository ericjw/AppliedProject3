#ifndef _PARSE_H
#define _PARSE_H

#include <iostream>
#include <fstream>
#include <QJsonDocument>
#include <vector>
#include <memory>
#include "sceneobjects.hpp"

class JSONParse {
public:
	//take in a file name, read into a QJsonDocument, 
	//and store values in the scene
	JSONParse() {};
	JSONParse(std::string fname);

	//read in all json key/value pairs and store as internal objects
	void parse(std::vector<std::unique_ptr<Object>>& objects);
	

	std::vector<Light> getLights();
	Camera getCam();

private:	

	//check for parse errors
	bool checkKeys();
	void checkCamValues();
	void checkLightValues();
	void checkPlaneValues(Plane p);
	void checkSphereValues(Sphere s);
	
	QJsonDocument jdoc;
	std::vector<Light> lights;
	Camera cam;
	
};

#endif // !_PARSE_H
