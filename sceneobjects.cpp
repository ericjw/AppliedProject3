#include "sceneobjects.hpp"
#include <cmath>

Camera::Camera(Center cent, double foc, Normal norm, double res[], int siz[])
{
	center = cent;
	focus = foc;
	normal = norm;
	resolution[0] = res[0];
	resolution[1] = res[1];
	size[0] = siz[0];
	size[1] = siz[1];
}

Camera::Camera() {
	
}

Sphere::Sphere(Center cent, Color col, double lamb, double rad)
{
	center = cent;
	color = col;
	lambert = lamb;
	radius = rad;
}

double Sphere::getIntersection(Ray r)
{
	Vect asdf = r.origin;
	Vect dir = r.direction;


	return 0.0;
}

Plane::Plane(Center cent, Normal norm, Color col, double lamb)
{
	center = cent;
	normal = norm;
	color = col;
	lambert = lamb;
}

double Plane::getIntersection(Ray r)
{
	Vect ray_dir = norm(r.direction);
	double a = dot(ray_dir, Vect(normal.x, normal.y, normal.z));

	if (a == 0) {
		//ray parallel
		return -1;
	}
	else {
		
	}

	return 0.0;
}

Light::Light(Location loc, double inten)
{
	location = loc;
	intensity = inten;
}
