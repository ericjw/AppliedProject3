#ifndef  _SCENE_OBJECTS_H
#define _SCENE_OBJECTS_H
#include "rayvect.hpp"

class Object
{
public:
	// virtual intersect function, needs to be overloaded by derived class
	virtual bool intersect(const Vect &orig, const Vect &dir, double &t) const = 0;
	virtual Vect getColor() const = 0;
	virtual ~Object() {} // virtual destructor 
	Object() {} // constructor 
};

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

class Sphere : public Object{
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


	Vect getColor() const;

	bool intersect(const Vect &orig, const Vect &dir, double &t) const;
};

class Plane : public Object{
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

	Vect getColor() const;
	
	bool intersect(const Vect &orig, const Vect &dir, double &t) const;
};

class Light {
public:
	struct Location {
		double x, y, z;
	} location;
	double intensity;

	Light(Location loc, double inten);
};


bool solveQuadratic(const double &a, const double &b, const double &c, double &x0, double &x1);

#endif // ! _SCENE_OBJECTS_H