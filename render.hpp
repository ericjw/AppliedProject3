#ifndef _RENDER_H
#define _RENDER_H
#undef max
#include "sceneobjects.hpp"
#include "rayvect.hpp"
#include <vector>
#include <memory>
#include <limits>
#include <mutex>

const double distInfinity = std::numeric_limits<double>::max();

class RayTracer {
public:
	RayTracer(std::vector<Light> li, Camera ca);

	Vect castRay(const Vect & orig, const Vect & dir, const std::vector<std::unique_ptr<Object>>& objects);
	void render(const std::vector<std::unique_ptr<Object>>& objects, const std::string &fname, const int &numThreads);
	bool trace(const Vect &orig, const Vect &dir, const std::vector<std::unique_ptr<Object>> &objects, double &distNear, const Object *&hitObject);	
	void renderPart(const std::vector<std::unique_ptr<Object>>& objects, const Vect & orig, const int & minY, const int & maxY, std::vector<std::tuple<double, double, Vect>>& pixels);

private:
	std::vector<Light> lights;
	Camera cam;
	std::mutex mut;
};

#endif // !_RENDER_H
