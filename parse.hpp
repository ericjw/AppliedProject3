#ifndef _PARSE_H
#define _PARSE_H

#include <iostream>
#include <fstream>
#include <QJsonDocument>

class JSONParse {
public:
	JSONParse(std::ifstream in);
private:
	QJsonDocument jdoc;
}

#endif // !_PARSE_H
