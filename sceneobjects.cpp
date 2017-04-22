#include "sceneobjects.hpp"

Camera::Camera(Center cent, double foc, Normal norm, double res[], int siz[])
{
	center = cent;
	focus = foc;
	normal = norm;
	resolution = res;
	size = siz;
}

Sphere::Sphere(Center cent, Color col, double lamb, double rad)
{
	center = cent;
	color = col;
	lambert = lamb;
	radius = rad;
}

Plane::Plane(Center cent, Normal norm, Color col, double lamb)
{
	center = cent;
	normal = norm;
	color = col;
	lambert = lamb;
}

Light::Light(Location loc, double inten)
{
	location = loc;
	intensity = inten;
}
