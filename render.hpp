#ifndef _RENDER_H
#define _RENDER_H
#include "sceneobjects.hpp"
#include "rayvect.hpp"
#include <vector>

class RayTracer {
public:
	RayTracer(std::vector<Light> li, std::vector<Sphere> sph, std::vector<Plane> pla, Camera ca);
private:
	std::vector<Light> lights;
	std::vector<Sphere> spheres;
	std::vector<Plane> planes;
	Camera cam;
};

#endif // !_RENDER_H
