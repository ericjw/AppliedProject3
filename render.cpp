#include "render.hpp"
#include <QColor>
#include <QImage>
#include <QDebug>

RayTracer::RayTracer(std::vector<Light> li, Camera ca)
{
	lights = li;
	cam = ca;
}


void RayTracer::render(const std::vector<std::unique_ptr<Object>> &objects, const std::string &fname) {
	QImage img(cam.size[1], cam.size[0], QImage::Format_RGB32);
	std::vector<std::vector<Vect>> pixelsX;

	Vect orig = Vect(cam.center.x, cam.center.y, cam.center.z) - (Vect(cam.normal.x, cam.normal.y, cam.normal.z) * cam.focus);
	for (int x = 0; x < cam.size[1]; x++) {
		std::vector<Vect> pixelsY;
		for (int y = 0; y < cam.size[0]; y++) {

			double i = cam.resolution[1] * (x - (cam.size[1]/2));
			double j = cam.resolution[0] * (y - (cam.size[0]/2));

			Vect dir = norm(Vect(i,j,0) - orig);
			Vect tmp = castRay(orig, dir, objects);
			pixelsY.push_back(tmp);
			//img.setPixel(x, y, QColor(tmp.x, tmp.y, tmp.z).rgb());
		}
		pixelsX.push_back(pixelsY);
	}

	double max = 0;
	for (auto vx : pixelsX) {
		for (auto vy : vx) {

			if (vy.x > max) {
				max = vy.x;
			}
			else if (vy.y > max) {
				max = vy.y;
			}
			else if (vy.z > max) {
				max = vy.z;
			}
		}
	}

	for (std::vector<Vect> &vx : pixelsX) {
		for (Vect &vy : vx) {
			double tmpScale = (255. / max);
			vy = vy * tmpScale;
		}
	}

	//double newmax = 0;
	//for (auto vx : pixelsX) {
	//	for (auto vy : vx) {
	//		if (vy.x > newmax) {
	//			newmax = vy.x;
	//		}
	//		else if (vy.y > newmax) {
	//			newmax = vy.y;
	//		}
	//		else if (vy.z > newmax) {
	//			newmax = vy.z;
	//		}
	//	}
	//}

	int x = 0;
	int y = 0;
	for (auto vx : pixelsX) {
		for (auto vy : vx) {
			img.setPixel(x, y, QColor((int)vy.x, (int)vy.y, (int)vy.z).rgb());
			y++;
		}
		x++;
		y = 0;
	}

	//for (auto vx : pixelsX) {
	//	for (auto vy : vx) {
	//		if (vy.x != 0 || vy.y != 0 ||vy.z != 0)
	//			qDebug() << "x " << vy.x << " y " << vy.y << " z " << vy.z;
	//	}

	//}

	qDebug() << "max " << max; // << " newmax " << newmax;

	img.save(fname.c_str());
}

bool RayTracer::trace(const Vect &orig, const Vect &dir, const std::vector<std::unique_ptr<Object>> &objects, double &distNear, const Object *&hitObject)
{
	distNear = distInfinity;

	for (std::vector<std::unique_ptr<Object>>::const_iterator iter = objects.begin(); iter != objects.end(); ++iter) {
		double dist = distInfinity;
		if ((*iter)->intersect(orig, dir, dist) && dist < distNear) {
			hitObject = iter->get();
			distNear = dist;
		}
	}

	return (hitObject != nullptr);
}

Vect RayTracer::castRay (const Vect &orig, const Vect &dir, const std::vector<std::unique_ptr<Object>> &objects)
{
	const Object *hitObject = nullptr; 
	double dist; 
	if (trace(orig, dir, objects, dist, hitObject)) {
		Vect col = hitObject->getColor();
		Vect totalCol = Vect(0, 0, 0);

		Vect point = orig + dir * dist;
		Vect nhit = hitObject->getCollisonNorm(point);
		double shadowDist;

		for (auto l : lights) {
			Vect shadow_ray(Vect(l.location.x, l.location.y, l.location.z) - point);
			const Object *testing = nullptr;
			//bool tmp = trace(point, norm(shadow_ray), objects, shadowDist, testing);
			//if not shadowed
			if (true){ //std::fabs(shadowDist) > 1 && !tmp) {
				double scale = dot(nhit, shadow_ray) * hitObject->getLambert();
				if (scale < 0) {
					scale = 0;
				}
				totalCol = totalCol + (col * (scale * l.intensity));
			}
		}
		return totalCol;
	}

	//if no objects hit
	return Vect(0, 0, 0);
}
