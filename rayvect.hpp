#ifndef _RAYVECT_H
#define _RAYVECT_H

class Vect {
public:
	Vect(double x_in, double y_in, double z_in);
	Vect();

	double x, y, z;
};

inline Vect operator+(Vect lhs, const Vect& rhs)
{
	lhs.x += rhs.x;
	lhs.y += rhs.y;
	lhs.z += rhs.z;

	return lhs;
}

inline Vect operator*(Vect lhs, const double& rhs)
{

	lhs.x *= rhs;
	lhs.y *= rhs;
	lhs.z *= rhs;

	return lhs;
}

inline Vect operator-(Vect lhs, const Vect& rhs)
{

	lhs.x -= rhs.x;
	lhs.y -= rhs.y;
	lhs.z -= rhs.z;

	return lhs;
}

//find dot product
double dot(Vect a, Vect b);
Vect norm(Vect arg);

#endif 
