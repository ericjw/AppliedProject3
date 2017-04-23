#include "render.hpp"

RayTracer::RayTracer(std::vector<Light> li, std::vector<Sphere> sph, std::vector<Plane> pla, Camera ca)
{
	lights = li;
	spheres = sph;
	planes = pla;
	cam = ca;
}
