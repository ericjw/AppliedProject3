#include "render.hpp"

RayTracer::RayTracer(std::vector<Light> li, std::vector<Sphere> sph, std::vector<Plane> pla, Camera ca)
{
	lights = li;
	spheres = sph;
	planes = pla;
	cam = ca;
}


//https://www.youtube.com/watch?v=4apLfBb9rbE 28:00