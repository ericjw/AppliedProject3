#include "sceneobjects.hpp"
#include <cmath>
#include <algorithm>

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

double Sphere::getIntersection(const Ray &r)
{
	double t0, t1;
	Vect L = r.origin - Vect(center.x, center.y, center.z);
	double a = dot(r.direction, r.direction);
	double b = 2 * dot(L, r.direction);
	double c = dot(L, L) - (radius * radius);

	double disc = b*b - 4 * a*c;
	if (disc > 0) {
		double firstRoot = ((-b - sqrt(disc)) / 2);
		if (firstRoot > 0) {
			// the first root is the smallest positive root
			return firstRoot;
		}
		else {
			// the second root is the smallest positive root
			double secondRoot = (-b + (sqrt(disc)) / 2);
			return secondRoot;
		}
	}
	else {
		//miss
		return -1;
	}
}


Plane::Plane(Center cent, Normal norm, Color col, double lamb)
{
	center = cent;
	normal = norm;
	color = col;
	lambert = lamb;
}

double Plane::getIntersection(const Ray &r)
{
	Vect ray_dir = norm(r.direction);
	Vect normVect = Vect(normal.x, normal.y, normal.z);

	double de = dot(Vect(normal.x, normal.y, normal.z), ray_dir);
	if (de > 1e-6) {
		Vect diff = Vect(center.x, center.y, center.z) - 
			Vect(r.origin.x, r.origin.y, r.origin.z);
		return dot(diff, normVect) / de;
	}

	return -1;
}

Light::Light(Location loc, double inten)
{
	location = loc;
	intensity = inten;
}
