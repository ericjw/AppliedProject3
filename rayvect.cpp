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

//Vect & Vect::operator+(const Vect & v)
//{
//	//Vect tmp(this->x + v.x, this->y + v.y, this->z + v.z);
//	//return tmp;
//
//	this->x += v.x;
//	this->y += v.y;
//	this->z += v.z;
//
//	return *this;
//}

//Vect & Vect::operator*(const double& d)
//{
//	//Vect tmp(this->x * d, this->y * d, this->z * d);
//	//return tmp;
//
//	this->x *= d;
//	this->y *= d;
//	this->z *= d;
//
//	return *this;
//}

//find dot product
double dot(Vect a, Vect b) {
	return (a.x*b.x + a.y*b.y + a.z*b.z);
}

//find unit normal vector
Vect norm(Vect arg) {
	double mag = sqrt(pow(arg.x, 2) + pow(arg.y, 2) + pow(arg.z, 2));
	return Vect(arg.x/mag, arg.y/mag, arg.z/mag);
}

Ray::Ray(Vect ori, Vect dir)
{
	origin = ori;
	direction = dir;
}
