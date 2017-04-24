#include "sceneobjects.hpp"
#include <cmath>
#include <algorithm>
#include <iostream>

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

Vect Sphere::getColor() const
{
	return Vect(color.r, color.g, color.b);
}

bool Sphere::intersect(const Vect & orig, const Vect & dir, double & t) const
{
	double t0, t1; // solutions for t if the ray intersects 

				  // analytic solution
	Vect L = orig - Vect(center.x, center.y, center.z);
	double a = dot(dir, dir);
	double b = 2 * dot(dir, L);
	double c = dot(L, L) - radius*radius;
	if (!solveQuadratic(a, b, c, t0, t1)) return false;
	if (t0 > t1) std::swap(t0, t1);

	if (t0 < 0) {
		t0 = t1; // if t0 is negative, let's use t1 instead 
		if (t0 < 0) return false; // both t0 and t1 are negative 
	}

	t = t0;

	return true;
}


Plane::Plane(Center cent, Normal norm, Color col, double lamb)
{
	center = cent;
	normal = norm;
	color = col;
	lambert = lamb;
}

Vect Plane::getColor() const
{
	return Vect(color.r, color.g, color.b);
}

bool Plane::intersect(const Vect & orig, const Vect & dir, double & t) const
{
	//// assuming vectors are all normalized
	//Vect n(normal.x, normal.y, normal.z);
	//double denom = dot( n, dir);
	//if (denom > 1e-6) {
	//	Vect p0l0 = norm(Vect(center.x, center.y, center.z)) - orig;
	//	t = dot(p0l0, n) / denom;
	//	if (t >= 0) {
	//		std::cout << "here";
	//	}
	//	return (t >= 0);
	//}

	//return false;

	Vect center(center.x, center.y, center.z);
	Vect n = norm(Vect(normal.x, normal.y, normal.z));
	double denom = dot(n, dir);
	if (denom > .00001) {
		t = -dot(center - orig, n) / denom;
		if (t >= 0) {
			//std::cout << "here";
			return true;
		}
	}

	return false;
}

Light::Light(Location loc, double inten)
{
	location = loc;
	intensity = inten;
}

bool solveQuadratic(const double &a, const double &b, const double &c, double &x0, double &x1)
{
	double discr = b * b - 4 * a * c;
	if (discr < 0) return false;
	else if (discr == 0) {
		x0 = x1 = -0.5 * b / a;
	}
	else {
		double q = (b > 0) ?
			-0.5 * (b + sqrt(discr)) :
			-0.5 * (b - sqrt(discr));
		x0 = q / a;
		x1 = c / q;
	}

	return true;
}
