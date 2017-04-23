#include "render.hpp"
#include <QColor>
#include <QImage>

RayTracer::RayTracer(std::vector<Light> li, std::vector<Sphere> sph, std::vector<Plane> pla, Camera ca)
{
	lights = li;
	spheres = sph;
	planes = pla;
	cam = ca;
}

void RayTracer::render() {
	std::vector<double> sphereIntersect;
	std::vector<double> planeIntersect;

	QImage img(cam.size[1], cam.size[0], QImage::Format_RGB32);
	for (int x = 0; x < cam.size[1]; x++) {
		for (int y = 0; y < cam.size[0]; y++) {

			Ray r(Vect(cam.center.x, cam.center.y, cam.center.z), 
				norm(Vect(1,2,3)));
			for (auto s : spheres) {
				sphereIntersect.push_back(s.getIntersection(r));
			}
			for (auto p : planes) {
				planeIntersect.push_back(p.getIntersection(r));
			}

			int sMinAboveZero = 1e10; //very large value -> indicates background color
			int sIndex = -1;
			for (int i = 0; i < sphereIntersect.size(); i++) {
				if (sphereIntersect.at(i) > 0 && sphereIntersect.at(i) < sMinAboveZero) {
					sMinAboveZero = sphereIntersect.at(i);

				}
			}
			int pMinAboveZero = 1e10;
			int pIndex = -1;
			for (int i = 0; i < planeIntersect.size(); i++) {
				if (planeIntersect.at(i) > 0 && planeIntersect.at(i) < pMinAboveZero) {
					pMinAboveZero = planeIntersect.at(i);
				}
			}
			if (pIndex == -1 && sIndex == -1) {
				//black backround
				img.setPixelColor(x, y, Qt::black);
			}
			else {
				if (sMinAboveZero < pMinAboveZero) {
					//sphere at point
					Sphere curr = spheres.at(sIndex);
					img.setPixelColor(x, y, QColor(curr.color.r, curr.color.g, curr.color.b));
				}
				else {
					//plane at point
					Plane curr = planes.at(pIndex);
					img.setPixelColor(x, y, QColor(curr.color.r, curr.color.g, curr.color.b));
				}
			}
		}

		img.save("output.png");
	}


}


//https://www.youtube.com/watch?v=4apLfBb9rbE 28:00