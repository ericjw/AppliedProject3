#ifndef _RAYVECT_H
#define _RAYVECT_H

class RayVect {
public:
	RayVect(double x_in, double y_in, double z_in);

	double x, y, z;
private:

};

//find dot product
double dot(RayVect a, RayVect b);
RayVect norm(RayVect arg);

#endif 
