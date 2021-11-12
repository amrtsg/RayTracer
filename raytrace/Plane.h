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

class Plane
{
public:
	//bounding the channel wise pixel color between 0 to 255
	uchar Clamp(int color)
	{
		if (color < 0) return 0;
		if (color >= 255) return 255;
		return color;
	}

	Plane() {};
	Plane(Vec3 center, Vec3 normal) :planeCenter(center), planeNormal(normal) {};

	void PlaneIntersect(Vec3 CameraPoint, Vec3 LightSource, Image image, Colour ambient);

public:
	Vec3 planeCenter, planeNormal;
	
};

