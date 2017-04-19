#ifndef  _SCENE_OBJECTS_H
#define _SCENE_OBJECTS_H

class Camera {
public:
	
	struct Center {
		double x, y, z;
	} center;
	double focus;
	struct Normal {
		double x, y, z;
	} normal;
	int* resolution;
	double* size;
	
	Camera(Center cent, double foc, Normal norm, int res[], double siz[]);
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