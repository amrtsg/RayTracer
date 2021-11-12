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

class Texture
{
public:

	Colour tex_lookup(Texture t, float u, float v);


public:

	
};

