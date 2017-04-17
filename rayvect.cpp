#include "rayvect.hpp"
#include <cmath>

RayVect::RayVect(double x_in, double y_in, double z_in) {
	x = x_in;
	y = y_in;
	z = z_in;
}

//find dot product
double dot(RayVect a, RayVect b) {
	return (a.x*b.x + a.y*b.y + a.z*b.z);
}

//find unit normal vector
RayVect norm(RayVect arg) {
	double mag = sqrt(pow(arg.x, 2) + pow(arg.y, 2) + pow(arg.z, 2));
	return RayVect(arg.x/mag, arg.y/mag, arg.z/mag); 
}