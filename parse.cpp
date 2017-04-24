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
		throw std::invalid_argument("Error: Bad JSON file name");
	}

	jdoc = QJsonDocument().fromJson(infile.readAll());
}

JSONParse::JSONParse() {

}

void JSONParse::parse(std::vector<std::unique_ptr<Object>> &objects) {
	QJsonObject obj = jdoc.object();
	QJsonObject camer = obj["camera"].toObject();
	QJsonObject center = camer["center"].toObject();
	QJsonObject norm = camer["normal"].toObject();

	QJsonArray res = camer["resolution"].toArray();
	QJsonArray size = camer["size"].toArray();
	double resol[] = { res.at(0).toDouble(), res.at(1).toDouble() };
	int siz[] = {size.at(0).toInt(), size.at(1).toInt()};

	//create camera object from json file
	cam = Camera(Camera::Center{ center["x"].toDouble(), center["y"].toDouble(), center["z"].toDouble() },
		camer["focus"].toDouble(), Camera::Normal{ norm["x"].toDouble(), norm["y"].toDouble(), norm["z"].toDouble() },
		resol, siz);

	//create light objects from json file
	QJsonArray lightsinscene = obj["lights"].toArray();
	for (auto l : lightsinscene) {
		QJsonObject curr = l.toObject();
		QJsonObject loc = curr["location"].toObject();
		lights.push_back(Light(Light::Location{loc["x"].toDouble(), loc["y"].toDouble(), loc["z"].toDouble()}, curr["intensity"].toDouble()));
	}

	//create plane and sphere objects from json file
	QJsonArray objectsinscene = obj["objects"].toArray();
	for (auto o : objectsinscene) {
		QJsonObject curr = o.toObject();
		if (curr["type"].toString() == "sphere") {
			QJsonObject loc = curr["center"].toObject();
			QJsonObject col = curr["color"].toObject();

			objects.push_back(std::unique_ptr<Object>(new Sphere(Sphere::Center{ loc["x"].toDouble(), loc["y"].toDouble(), loc["z"].toDouble() },
				Sphere::Color{ col["r"].toDouble(), col["g"].toDouble(), col["b"].toDouble() },
				curr["lambert"].toDouble(), curr["radius"].toDouble())));
		}
		else if (curr["type"].toString() == "plane") {
			QJsonObject norm = curr["normal"].toObject();
			QJsonObject loc = curr["center"].toObject();
			QJsonObject col = curr["color"].toObject();

			objects.push_back(std::unique_ptr<Object>(new Plane(Plane::Center{ loc["x"].toDouble(), loc["y"].toDouble(), loc["z"].toDouble() },
				Plane::Normal{norm["x"].toDouble(), norm["y"].toDouble(), norm["z"].toDouble()}, 
				Plane::Color{ col["r"].toDouble(), col["g"].toDouble(), col["b"].toDouble() }, 
				curr["lambert"].toDouble())));
		}
	}
}


std::vector<Light> JSONParse::getLights()
{
	return lights;
}


Camera JSONParse::getCam()
{
	return cam;
}


