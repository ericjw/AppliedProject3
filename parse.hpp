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
	JSONParse();
	JSONParse(std::string fname);
//	JSONParse(std::vector<std::unique_ptr<Object>> &objects);

	//read in all json key/value pairs and store as internal objects

	void parse(std::vector<std::unique_ptr<Object>>& objects);

	//getters
	/*std::vector<Sphere> getSpheres();
	std::vector<Plane> getPlanes();*/

	std::vector<Light> getLights();
	Camera getCam();
	//std::vector<std::unique_ptr<Object>>& getObjects();

private:
	QJsonDocument jdoc;
//	std::vector<Sphere> spheres;
	std::vector<Light> lights;
//	std::vector<Plane> planes;
	Camera cam;
	
};

#endif // !_PARSE_H
