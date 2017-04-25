#ifndef _RENDER_H
#define _RENDER_H
#undef max
#include "sceneobjects.hpp"
#include "rayvect.hpp"
#include <vector>
#include <memory>
#include <limits>

const double distInfinity = std::numeric_limits<double>::max();

class RayTracer {
public:
	RayTracer(std::vector<Light> li, Camera ca);

	Vect castRay(const Vect & orig, const Vect & dir, const std::vector<std::unique_ptr<Object>>& objects);
	void render(const std::vector<std::unique_ptr<Object>>& objects, const std::string &fname);
	bool trace(const Vect &orig, const Vect &dir, const std::vector<std::unique_ptr<Object>> &objects, double &distNear, const Object *&hitObject);


private:
	std::vector<Light> lights;
	Camera cam;
};

#endif // !_RENDER_H
