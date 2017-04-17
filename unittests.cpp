#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "parse.hpp"
#include "rayvect.hpp"

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

	RayVect anorm = norm(a);
	REQUIRE(anorm.x == Approx(3/sqrt(14)));
	REQUIRE(anorm.y == Approx(sqrt(2./7)));
	REQUIRE(anorm.z == Approx(1 / sqrt(14)));
	RayVect bnorm = norm(b);
	REQUIRE(bnorm.x == Approx(2*sqrt(5)/7));
	REQUIRE(bnorm.y == Approx(9/(7*sqrt(5))));
	REQUIRE(bnorm.z == Approx(8 / (7 * sqrt(5))));
}

TEST_CASE("Test JSON Parsing", "[JSON]") {
	JSONParse x("/vagrant/tests/scene0.json");
}
