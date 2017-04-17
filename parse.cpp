#include "parse.hpp"
#include <QFile>
#include <exception>
#include <QDebug>

JSONParse::JSONParse(std::string fname) {
	QFile infile(fname.c_str());

	//handle bad file error
	if (!infile.open(QFile::ReadOnly )) {
		//infile.close();
		throw std::invalid_argument("Error: Bad JSON file name");
	}

	jdoc = QJsonDocument().fromJson(infile.readAll());
	//QString strJson(jdoc.toJson(QJsonDocument::Indented));
	//qDebug() << strJson;
	//printf("%s",strJson.toStdString().c_str());
}