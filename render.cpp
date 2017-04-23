#include "render.hpp"

RayTracer::RayTracer(std::vector<Light> li, std::vector<Sphere> sph, std::vector<Plane> pla, Camera ca)
{
	lights = li;
	spheres = sph;
	planes = pla;
	cam = ca;
}

void RayTracer::render() {
	for (int x = 0; x < cam.size[1]; x++) {
		for (int y = 0; y < cam.size[0]; y++) {
			//pixel by pixel here
		}
	}
}


//https://www.youtube.com/watch?v=4apLfBb9rbE 28:00