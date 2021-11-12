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

static Vec3 LightSource = Vec3(2, 1, 0); //2, 1, 0
static Colour specular = Colour(255, 255, 255);
static Colour triangleDiffuse = Colour(100, 100, 100);//255, 255, 255
static Colour sphereDiffuse = Colour(90, 90, 90);
static Vec3 CameraPoint = Vec3(0, 0, 0); // Origin = Vec3(0, 0, 0)
static Vec3 eps = Vec3(-1.1, -0.3, 4); // Origin = Vec3(0, 0, 0)

class Lights
{
public:

};

