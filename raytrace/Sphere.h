#pragma once
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include<math.h>
#include<Image.h>
#include<Triangle.h>

//Data types
typedef float Scalar;
typedef Eigen::Matrix<Scalar, 3, 1> Vec3;
typedef Eigen::Matrix<Scalar, 2, 1> Vec2;
typedef	unsigned char uchar;
using Colour = cv::Vec3b;

class Sphere
{

public:
	uchar Clamp(int color)
	{
		if (color < 0) return 0;
		if (color >= 255) return 255;
		return color;
	}

	Sphere(Vec3 center, float radius, Colour amb) :sphereCenter(center), sphereRadius(radius), ambient(amb){};

	bool SphereIntersect(Triangle::intersectInfo& s);
	bool checkShadow(Triangle::intersectInfo& s, Vec3& shadowRay);

public:
	Vec3 sphereCenter;
	float sphereRadius;
	Colour ambient;

};

