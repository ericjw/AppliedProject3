#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

//handle testing on windows/unix
#ifdef _WIN32
std::string testFilePath = "C:\\Users\\ejwal\\Documents\\ECE 3574\\project3-ericjw\\tests\\scene2.json";
#else
std::string testFilePath = "/vagrant/tests/scene2.json";
#endif

#include "parse.hpp"
#include "rayvect.hpp"
#include "sceneobjects.hpp"
#include "render.hpp"
#include <QDebug>

TEST_CASE("tests vector creation and operations", "[rayvect]") {
	Vect a(3, 2, 1), b(10, 9, 8), c(5, 0, 0);
	REQUIRE(a.x == Approx(3));
	REQUIRE(a.y == Approx(2));
	REQUIRE(a.z == Approx(1));

	REQUIRE(b.x == Approx(10));
	REQUIRE(b.y == Approx(9));
	REQUIRE(b.z == Approx(8));

	REQUIRE(c.x == Approx(5));
	REQUIRE(c.y == Approx(0));
	REQUIRE(c.z == Approx(0));

	REQUIRE(dot(a, b) == Approx(56));
	REQUIRE(dot(a, c) == Approx(15));
	REQUIRE(dot(b, c) == Approx(50));

	//unit normal
	Vect anorm = norm(a);
	REQUIRE(anorm.x == Approx(3/sqrt(14)));
	REQUIRE(anorm.y == Approx(sqrt(2./7)));
	REQUIRE(anorm.z == Approx(1 / sqrt(14)));

	//dot product
	Vect bnorm = norm(b);
	REQUIRE(bnorm.x == Approx(2*sqrt(5)/7));
	REQUIRE(bnorm.y == Approx(9/(7*sqrt(5))));
	REQUIRE(bnorm.z == Approx(8 / (7 * sqrt(5))));

	//overloaded operators
	Vect mult = a * -3;
	REQUIRE(mult.x == -9);
	REQUIRE(mult.y == -6);
	REQUIRE(mult.z == -3);

	Vect test = b + a;
	REQUIRE(test.x == 13);
	REQUIRE(test.y == 11);
	REQUIRE(test.z == 9);

}


TEST_CASE("Test creation of sphere and plane", "[sceneobjects]") {
	Plane p1(Plane::Center{ 1.2, 2.3, 4.5 }, Plane::Normal{0., 0., 1.},
		Plane::Color{255., 128.9, 0.}, 1.);
	Sphere s1(Sphere::Center{ 1.2, 2.3, 4.5 }, Sphere::Color{ 123., 10., 17. }, 1., 3.14);

	//plane
	REQUIRE(p1.center.x == 1.2);
	REQUIRE(p1.center.y == 2.3);
	REQUIRE(p1.center.z == 4.5);

	REQUIRE(p1.color.r== 255.);
	REQUIRE(p1.color.g == 128.9);
	REQUIRE(p1.color.b == 0.);

	REQUIRE(p1.normal.x == 0.);
	REQUIRE(p1.normal.y == 0.);
	REQUIRE(p1.normal.z == 1.);

	REQUIRE(p1.lambert == 1.);

	//sphere
	REQUIRE(s1.center.x == 1.2);
	REQUIRE(s1.center.y == 2.3);
	REQUIRE(s1.center.z == 4.5);

	REQUIRE(s1.color.r == 123.);
	REQUIRE(s1.color.g == 10.);
	REQUIRE(s1.color.b == 17.);

	REQUIRE(s1.radius == 3.14);

	REQUIRE(s1.lambert == 1.);
}

TEST_CASE("Test creation of light and camera", "[sceneobjects]") {
	//camera
	double a[] = { 256., 256. };
	int b[] = {1000, 500};
	Camera cam(Camera::Center{ 3., 2., 1. }, 7.7, Camera::Normal{ 0., 0., 1. }, a, b);
	
	REQUIRE(cam.center.x == 3.);
	REQUIRE(cam.center.y == 2.);
	REQUIRE(cam.center.z == 1.);

	REQUIRE(cam.normal.x == 0.);
	REQUIRE(cam.normal.y == 0.);
	REQUIRE(cam.normal.z == 1.);

	REQUIRE(cam.focus == 7.7);

	REQUIRE(cam.resolution[0] == 256.);
	REQUIRE(cam.resolution[1] == 256.);

	REQUIRE(cam.size[0] == 1000);
	REQUIRE(cam.size[1] == 500);

	//light
	Light li(Light::Location{33., 44, 55.}, 9000.1);
	REQUIRE(li.location.x == 33.);
	REQUIRE(li.location.y == 44.);
	REQUIRE(li.location.z == 55.);

	REQUIRE(li.intensity == 9000.1);
}

TEST_CASE("Test JSON Parsing", "[JSON]") {
	REQUIRE_THROWS_AS(JSONParse oops("bad/file/name.json"), std::invalid_argument);

	std::vector<std::unique_ptr<Object>> objects;
	JSONParse a(testFilePath);
	//JSONParse a("C:\\Users\\ejwal\\Documents\\ECE 3574\\project3-ericjw\\tests\\scene2.json");
	//JSONParse a("/vagrant/tests/scene2.json");
	a.parse(objects);

	Camera cam = a.getCam();
	std::vector<Light> lights = a.getLights();

	REQUIRE(lights.size() == 64);
	REQUIRE(objects.size() == 9);

	//camera
	REQUIRE(cam.center.x == 0);
	REQUIRE(cam.center.y == 0);
	REQUIRE(cam.center.z == 0);
	REQUIRE(cam.focus == 10);
	REQUIRE(cam.normal.x == 0);
	REQUIRE(cam.normal.y == 0);
	REQUIRE(cam.normal.z == 1);
	REQUIRE(cam.resolution[0] == 0.01);
	REQUIRE(cam.resolution[1] == 0.01);
	REQUIRE(cam.size[0] == 1024);
	REQUIRE(cam.size[1] == 1024);

	//lights
	Light l1 = lights.at(0);
	REQUIRE(l1.intensity == 0.6);
	REQUIRE(l1.location.x == 0);
	REQUIRE(l1.location.y == 0);
	REQUIRE(l1.location.z == -10);
}

TEST_CASE("Test bad JSON files parsing", "[JSON]") {

	std::vector<std::unique_ptr<Object>> objects;

	JSONParse bad("/vagrant/tests/scene4.json");
	REQUIRE_THROWS_AS(bad.parse(objects), std::invalid_argument);

	bad = JSONParse("/vagrant/tests/scene3.json");
	REQUIRE_THROWS_AS(bad.parse(objects), std::invalid_argument);

	for (int i = 1; i <= 13; i++) {
		std::string file = "/vagrant/tests/badfiles/badparse" + std::to_string(i) + ".json";
		bad = JSONParse(file.c_str());
		REQUIRE_THROWS_AS(bad.parse(objects), std::invalid_argument);
	}

	for (int i = 1; i <= 4; i++) {
		std::string file = "/vagrant/tests/badfiles/badvalue" + std::to_string(i) + ".json";
		bad = JSONParse(file.c_str());
		REQUIRE_THROWS_AS(bad.parse(objects), std::invalid_argument);
	}
}

TEST_CASE("test rendering class", "[render]") {
	std::vector<std::unique_ptr<Object>> objects;
	JSONParse a("/vagrant/tests/scene1.json");
	a.parse(objects);
	RayTracer tracer(a.getLights(), a.getCam());
	tracer.render(objects, "output.png", 1);
}

TEST_CASE("threading", "[test that multiple threads run]") {
	std::vector<std::unique_ptr<Object>> objects;
	JSONParse a("/vagrant/tests/scene1.json");
	a.parse(objects);
	RayTracer tracer(a.getLights(), a.getCam());
	tracer.render(objects, "output.png", 4);
}