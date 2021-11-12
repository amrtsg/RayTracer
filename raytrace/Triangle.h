#pragma once
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include<math.h>
#include<Image.h>

//Data types
typedef float Scalar;
typedef Eigen::Matrix<Scalar, 3, 1> Vec3;
typedef Eigen::Matrix<Scalar, 2, 1> Vec2;
typedef	unsigned char uchar;
using Colour = cv::Vec3b;

class Triangle
{
public:
	Triangle() {};
	Triangle(Vec3 v1, Vec3 v2, Vec3 v3, Colour amb) :vertex1_(v1), vertex2_(v2), vertex3_(v3), ambient(amb) {		
		normal_ = ComputeNormal(v1, v2, v3);
	};

	struct intersectInfo {
		float tVal;
		Vec3 pixelColour;
		Vec3 dir;
		Vec3 POI;
		Colour amb;
	};

	Vec3 BaryCentric(const Vec3&);		
	Vec3 ComputeNormal(const Vec3&, const Vec3&, const Vec3&);
	bool TriangleIntersect(intersectInfo& s);

public:
	Vec3 vertex1_, vertex2_, vertex3_;
	Vec3 normal_;
	Colour ambient;
	
};

