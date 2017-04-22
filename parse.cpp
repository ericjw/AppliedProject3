#include "parse.hpp"
#include <QFile>
#include <exception>
#include <QDebug>
#include "QJsonArray"
#include <QJsonObject>
#include <QJsonValue>

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

void JSONParse::parse() {
	QJsonObject obj = jdoc.object();
	QJsonObject camer = obj["camera"].toObject();
	QJsonObject center = camer["center"].toObject();
	QJsonObject norm = camer["normal"].toObject();

	QJsonArray res = camer["resolution"].toArray();
	QJsonArray size = camer["size"].toArray();
	double resol[] = { res.at(0).toDouble(), res.at(1).toDouble() };
	int siz[] = {size.at(0).toInt(), size.at(1).toInt()};

	Camera cam = Camera(Camera::Center{ center["x"].toDouble(), center["y"].toDouble(), center["z"].toDouble() },
		camer["focus"].toDouble(), Camera::Normal{ norm["x"].toDouble(), norm["y"].toDouble(), norm["z"].toDouble() },
		resol, siz);

	/*qDebug() << cam.center.x;
	qDebug() << cam.center.y;
	qDebug() << cam.center.z;

	qDebug() << cam.focus;

	qDebug() << cam.normal.x;
	qDebug() << cam.normal.y;
	qDebug() << cam.normal.z;

	qDebug() << cam.size[0];
	qDebug() << cam.size[1];

	qDebug() << cam.resolution[0];
	qDebug() << cam.resolution[1];*/

	QJsonArray lightsinscene = obj["lights"].toArray();
	for (auto l : lightsinscene) {
		QJsonObject tmp = l.toObject();
		QJsonObject loc = tmp["location"].toObject();
		lights.push_back(Light(Light::Location{loc["x"].toDouble(), loc["y"].toDouble(), loc["z"].toDouble()}, tmp["intensity"].toDouble()));
	}

	/*for (auto l : lights) {
		qDebug() << l.intensity;

		qDebug() << l.location.x;
		qDebug() << l.location.y;
		qDebug() << l.location.z;
	}*/
}