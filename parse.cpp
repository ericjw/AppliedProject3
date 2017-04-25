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
	if (!checkKeys()) {
		throw std::invalid_argument("Error: Key missing in JSON file");
	}

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
	checkCamValues();

	//create light objects from json file
	QJsonArray lightsinscene = obj["lights"].toArray();
	for (auto l : lightsinscene) {
		QJsonObject curr = l.toObject();
		QJsonObject loc = curr["location"].toObject();
		lights.push_back(Light(Light::Location{loc["x"].toDouble(), loc["y"].toDouble(), loc["z"].toDouble()}, curr["intensity"].toDouble()));
	}
	checkLightValues();

	//create plane and sphere objects from json file
	QJsonArray objectsinscene = obj["objects"].toArray();
	for (auto o : objectsinscene) {
		QJsonObject curr = o.toObject();
		if (curr["type"].toString() == "sphere") {
			QJsonObject loc = curr["center"].toObject();
			QJsonObject col = curr["color"].toObject();
			checkSphereValues(Sphere(Sphere::Center{ loc["x"].toDouble(), loc["y"].toDouble(), loc["z"].toDouble() },
				Sphere::Color{ col["r"].toDouble(), col["g"].toDouble(), col["b"].toDouble() },
				curr["lambert"].toDouble(), curr["radius"].toDouble()));

			objects.push_back(std::unique_ptr<Object>(new Sphere(Sphere::Center{ loc["x"].toDouble(), loc["y"].toDouble(), loc["z"].toDouble() },
				Sphere::Color{ col["r"].toDouble(), col["g"].toDouble(), col["b"].toDouble() },
				curr["lambert"].toDouble(), curr["radius"].toDouble())));
		}
		else if (curr["type"].toString() == "plane") {
			QJsonObject norm = curr["normal"].toObject();
			QJsonObject loc = curr["center"].toObject();
			QJsonObject col = curr["color"].toObject();
			checkPlaneValues(Plane(Plane::Center{ loc["x"].toDouble(), loc["y"].toDouble(), loc["z"].toDouble() },
				Plane::Normal{ norm["x"].toDouble(), norm["y"].toDouble(), norm["z"].toDouble() },
				Plane::Color{ col["r"].toDouble(), col["g"].toDouble(), col["b"].toDouble() },
				curr["lambert"].toDouble()));

			objects.push_back(std::unique_ptr<Object>(new Plane(Plane::Center{ loc["x"].toDouble(), loc["y"].toDouble(), loc["z"].toDouble() },
				Plane::Normal{norm["x"].toDouble(), norm["y"].toDouble(), norm["z"].toDouble()}, 
				Plane::Color{ col["r"].toDouble(), col["g"].toDouble(), col["b"].toDouble() }, 
				curr["lambert"].toDouble())));
		}
	}
}

bool JSONParse::checkKeys()
{
	QJsonObject obj = jdoc.object();
	if (!(obj.contains("camera") && obj.contains("lights") && obj.contains("objects"))) { return false; }

	//camera
	QJsonObject cam = obj["camera"].toObject();
	if (!(cam.contains("center") && cam.contains("focus") && cam.contains("normal") && cam.contains("resolution") && cam.contains("size"))) { return false; }

	QJsonObject cent = cam["center"].toObject();
	if (!(cent.contains("x") && cent.contains("y") && cent.contains("z"))) { return false; }

	QJsonObject norm = cam["normal"].toObject();
	if (!(norm.contains("x") && norm.contains("y") && norm.contains("z"))) { return false; }

	if (cam["resolution"].toArray().size() != 2 || cam["size"].toArray().size() != 2) { return false; }

	//lights
	for (auto li : obj["lights"].toArray()) {
		QJsonObject o = li.toObject();
		if (!(o.contains("intensity") && o.contains("location"))) { return false; }

		QJsonObject l = o["location"].toObject();
		if (!(l.contains("x") && l.contains("y") && l.contains("z"))) { return false; }
	}

	//objects
	for (auto ob : obj["objects"].toArray()) {
		QJsonObject o = ob.toObject();
		if (!(o.contains("center") && o.contains("color") && o.contains("lambert") && o.contains("type"))) { return false; }

		if (o["type"].toString() == "sphere") {
			if (!o.contains("radius")) { return false; }
		}
		else if (o["type"].toString() == "plane") {
			if (!o.contains("normal")) { return false; }
			QJsonObject n = o["normal"].toObject();
			if (!(n.contains("x") && n.contains("y") && n.contains("z"))) { return false; }
		}
		else { return false; }
		
		QJsonObject c = o["center"].toObject();
		if (!(c.contains("x") && c.contains("y") && c.contains("z"))) { return false; }

		c = o["color"].toObject();
		if (!(c.contains("r") && c.contains("g") && c.contains("b"))) { return false; }
	}
	return true;
}


std::vector<Light> JSONParse::getLights()
{
	return lights;
}


Camera JSONParse::getCam()
{
	return cam;
}

void JSONParse::checkCamValues()
{
	bool valid = true;
	if (cam.size[0] < 0 || cam.size[1] < 0 || cam.resolution[0] < 0 || cam.resolution[1] < 0) {
		valid = false;
	}

	if (!valid) {
		throw std::invalid_argument("Error: values provided are out of bounds");
	}
}

void JSONParse::checkLightValues()
{
	bool valid = true;
	for (auto l : lights) {
		if (l.intensity < 0) {
			valid = false;
		}
	}

	if (!valid) {
		throw std::invalid_argument("Error: values provided are out of bounds");
	}
}

void JSONParse::checkPlaneValues(Plane p)
{
	bool valid = true;
	if (p.lambert < 0 || p.lambert > 1 ||
		p.color.r < 0 || p.color.r > 255 || p.color.g < 0 || p.color.g > 255 || p.color.b < 0 || p.color.b > 255) {
		valid = false;
	}

	if (!valid) {
		throw std::invalid_argument("Error: values provided are out of bounds");
	}
}

void JSONParse::checkSphereValues(Sphere s)
{
	bool valid = true;
	if (s.radius < 0 || s.lambert < 0 || s.lambert > 1||
		s.color.r < 0 || s.color.r > 255 || s.color.g < 0 || s.color.g > 255 || s.color.b < 0 || s.color.b > 255) {
		valid = false;
	}

	if (!valid) {
		throw std::invalid_argument("Error: values provided are out of bounds");
	}
}


