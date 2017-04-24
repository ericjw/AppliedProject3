#include "render.hpp"
#include <QColor>
#include <QImage>



RayTracer::RayTracer(std::vector<Light> li, Camera ca)
{
	lights = li;
	cam = ca;
}


void RayTracer::render(const std::vector<std::unique_ptr<Object>> &objects) {
	QImage img(cam.size[1], cam.size[0], QImage::Format_RGB32);

	Vect orig = Vect(cam.center.x, cam.center.y, cam.center.z) - (Vect(cam.normal.x, cam.normal.y, cam.normal.z) * cam.focus);
	for (int x = 0; x < cam.size[1]; x++) {
		for (int y = 0; y < cam.size[0]; y++) {

			double i = cam.resolution[1] * (x - (cam.size[1]/2));
			double j = cam.resolution[0] * (y - (cam.size[0]/2));

			Vect dir = norm(Vect(i,j,0) - orig);
			Vect tmp = castRay(orig, dir, objects);
			img.setPixel(x, y, QColor(tmp.x, tmp.y, tmp.z).rgb());
		}
	}

	img.save("output.png");
}

bool RayTracer::trace(const Vect &orig, const Vect &dir, const std::vector<std::unique_ptr<Object>> &objects, double &distNear, const Object *&hitObject)
{
	distNear = kInfinity;
	std::vector<std::unique_ptr<Object>>::const_iterator iter = objects.begin();
	for (; iter != objects.end(); ++iter) {
		double dist = kInfinity;
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
		return hitObject->getColor();
	}

	return Vect(0, 0, 0);
}
