#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "parse.hpp"
#include "rayvect.hpp"
#include "sceneobjects.hpp"

// IMPORTANT NOTE:
// These are just a few examples from my solution and **should be removed**.
// Depending on your code design your class and functions names would differ

//#include "geometry.hpp"
//
//TEST_CASE( "Test Basic Geometry: Vec3d ", "[geometry]" ) {
//
//  Vec3d a(2,0,0), b(0,4,0);
//  
//  REQUIRE(a.x == Approx(2));
//  REQUIRE(a.y == Approx(0));
//  REQUIRE(a.z == Approx(0));
//
//  REQUIRE(b.x == Approx(0));
//  REQUIRE(b.y == Approx(4));
//  REQUIRE(b.z == Approx(0));
//
//  double adotb = dot(a,b);
//  REQUIRE(adotb == Approx(0));
//
//  Vec3d anorm = norm(a);
//  REQUIRE(anorm.x == Approx(1));
//  REQUIRE(anorm.y == Approx(0));
//  REQUIRE(anorm.z == Approx(0));
//
//  Vec3d bnorm = norm(b);
//  REQUIRE(bnorm.x == Approx(0));
//  REQUIRE(bnorm.y == Approx(1));
//  REQUIRE(bnorm.z == Approx(0));
//}

TEST_CASE("tests vector creation and operations", "[rayvect]") {
	RayVect a(3, 2, 1), b(10, 9, 8), c(5, 0, 0);
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
	RayVect anorm = norm(a);
	REQUIRE(anorm.x == Approx(3/sqrt(14)));
	REQUIRE(anorm.y == Approx(sqrt(2./7)));
	REQUIRE(anorm.z == Approx(1 / sqrt(14)));

	//dot product
	RayVect bnorm = norm(b);
	REQUIRE(bnorm.x == Approx(2*sqrt(5)/7));
	REQUIRE(bnorm.y == Approx(9/(7*sqrt(5))));
	REQUIRE(bnorm.z == Approx(8 / (7 * sqrt(5))));
}

TEST_CASE("Test JSON Parsing", "[JSON]") {
	JSONParse x("/vagrant/tests/scene0.json");
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
	int a[] = { 256, 256 };
	double b[] = {1000., 500.};
	Camera cam(Camera::Center{ 3., 2., 1. }, 7.7, Camera::Normal{ 0., 0., 1. }, a, b);
	
	REQUIRE(cam.center.x == 3.);
	REQUIRE(cam.center.y == 2.);
	REQUIRE(cam.center.z == 1.);

	REQUIRE(cam.normal.x == 0.);
	REQUIRE(cam.normal.y == 0.);
	REQUIRE(cam.normal.z == 1.);

	REQUIRE(cam.focus == 7.7);

	REQUIRE(cam.resolution[0] == 256);
	REQUIRE(cam.resolution[1] == 256);

	REQUIRE(cam.size[0] == 1000.);
	REQUIRE(cam.size[1] == 500.);

	//light
	Light li(Light::Location{33., 44, 55.}, 9000.1);
	REQUIRE(li.location.x == 33.);
	REQUIRE(li.location.y == 44.);
	REQUIRE(li.location.z == 55.);

	REQUIRE(li.intensity == 9000.1);
}