#include "render.hpp"
#include <QColor>
#include <QImage>



RayTracer::RayTracer(std::vector<Light> li, Camera ca)
{
	lights = li;
	cam = ca;
}


void RayTracer::render(const std::vector<std::unique_ptr<Object>> &objects, const std::string &fname) {
	QImage img(cam.size[1], cam.size[0], QImage::Format_RGB32);
	//std::vector<std::vector<Vect>> pixelsX;

	Vect orig = Vect(cam.center.x, cam.center.y, cam.center.z) - (Vect(cam.normal.x, cam.normal.y, cam.normal.z) * cam.focus);
	for (int x = 0; x < cam.size[1]; x++) {
		//std::vector<Vect> pixelsY;
		for (int y = 0; y < cam.size[0]; y++) {

			double i = cam.resolution[1] * (x - (cam.size[1]/2));
			double j = cam.resolution[0] * (y - (cam.size[0]/2));

			Vect dir = norm(Vect(i,j,0) - orig);
			Vect tmp = castRay(orig, dir, objects);
			//pixelsY.push_back(tmp);
			img.setPixel(x, y, QColor(tmp.x, tmp.y, tmp.z).rgb());
		}
		//pixelsX.push_back(pixelsY);
	}

	/*int x = 0;
	int y = 0;
	for (auto vx : pixelsX) {
		for (auto vy : vx) {
			img.setPixel(x, y, QColor(vy.x, vy.y, vy.z).rgb());
			y++;
		}
		x++;
		y = 0;
	}*/

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
		Vect nhit = norm(point - Vect(hitObject->getCenter()));
		Vect shadow_ray(Vect(lights.at(0).location.x, lights.at(0).location.y, lights.at(0).location.z));

		for (auto l : lights) {
			//if not shadowed
			if (true) {
				double scale = dot(nhit, shadow_ray) * hitObject->getLambert();
				totalCol = totalCol + (col * scale * l.intensity);
			}

		}
		return col;
	}

	return Vect(0, 0, 0);
}
