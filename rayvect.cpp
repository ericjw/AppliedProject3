#include "rayvect.hpp"
#include <cmath>

Vect::Vect(double x_in, double y_in, double z_in) {
	x = x_in;
	y = y_in;
	z = z_in;
}

Vect::Vect() {
	x = 0;
	y = 0;
	z = 0;
}

//find dot product
double dot(Vect a, Vect b) {
	return (a.x*b.x + a.y*b.y + a.z*b.z);
}

//find unit normal vector
Vect norm(Vect arg) {
	double mag = sqrt(pow(arg.x, 2) + pow(arg.y, 2) + pow(arg.z, 2));
	return Vect(arg.x/mag, arg.y/mag, arg.z/mag);
}

