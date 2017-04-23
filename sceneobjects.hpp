#ifndef  _SCENE_OBJECTS_H
#define _SCENE_OBJECTS_H
#include "rayvect.hpp"

class Camera {
public:
	
	struct Center {
		double x, y, z;
	} center;
	double focus;
	struct Normal {
		double x, y, z;
	} normal;
	double resolution[2];
	int size[2];
	
	Camera(Center cent, double foc, Normal norm, double res[], int siz[]);
	Camera();
};

class Sphere {
public:
	double radius;
	struct Center {
		double x, y, z;
	} center;

	struct Color {
		double r, g, b;
	} color;
	double lambert;
	
	Sphere(Center cent, Color col, double lamb, double rad);

	double getIntersection(Ray r);
};

class Plane {
public:
	struct Normal {
		double x, y, z;
	} normal;

	struct Center {
		double x, y, z;
	} center;

	struct Color {
		double r, g, b;
	} color;

	double lambert;

	Plane(Center cent, Normal norm, Color col, double lamb);
	
	double getIntersection(Ray r);
};

class Light {
public:
	struct Location {
		double x, y, z;
	} location;
	double intensity;

	Light(Location loc, double inten);
};

#endif // ! _SCENE_OBJECTS_H