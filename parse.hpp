#ifndef _PARSE_H
#define _PARSE_H

#include <iostream>
#include <fstream>
#include <QJsonDocument>

class JSONParse {
public:
	//take in a file name, read into a QJsonDocument, 
	//and store values in the scene
	JSONParse(std::string fname);

private:
	QJsonDocument jdoc;
};

#endif // !_PARSE_H
