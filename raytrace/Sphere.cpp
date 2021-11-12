#include "Sphere.h"
#include "Triangle.h"
#include "Lights.h"
#include <iostream>
#include <math.h>
using namespace std;


bool Sphere::SphereIntersect(Triangle::intersectInfo& s) {

	Vec3 ray = CameraPoint - sphereCenter;

	//find A B and C to compute discriminant
	float A = s.dir.dot(s.dir);
	float B = s.dir.dot(ray) * 2;
	float C = ray.dot(ray) - pow(sphereRadius, 2);

	//compute the discriminant
	float discriminant = pow(B, 2) - (4 * A * C);

	//if the discriminant is greater than zero
	if (discriminant > 0) {
		//find roots t1 and t2
		float t1 = (-B - sqrt(discriminant)) / (2 * A);
		float t2 = (-B + sqrt(discriminant)) / (2 * A);

		//determine which one is the real intersection point
		float t = std::min(t1, t2);

		if (t > 0) {
			//Shading                
			s.POI = CameraPoint + (s.dir * t);
			Vec3 Normal = s.POI - sphereCenter;
			Normal.normalize();

			Vec3 LightVector = LightSource - s.POI;
			LightVector.normalize();

			Vec3 viewVec = CameraPoint - s.POI;
			viewVec.normalize();

			float dotNL = Normal.dot(LightVector);
			Vec3 h = (viewVec + LightVector) / ((viewVec + LightVector)).norm();

			float diffuseTerm = LightVector.dot(Normal);
			float specularTerm = (pow(Normal.dot(h), 128));
			if (diffuseTerm < 0) diffuseTerm = 0;
			if (specularTerm < 0) specularTerm = 0;
			
			s.pixelColour[0] = (ambient[0] + (sphereDiffuse[0] * diffuseTerm) + (specular[0] * specularTerm));
			s.pixelColour[1] = (ambient[1] + (sphereDiffuse[1] * diffuseTerm) + (specular[1] * specularTerm));
			s.pixelColour[2] = (ambient[2] + (sphereDiffuse[2] * diffuseTerm) + (specular[2] * specularTerm));
			s.tVal = t;
			s.amb = ambient;
			return true;
		}
	}
	else {
		s.pixelColour[0] = 0;
		s.pixelColour[1] = 0;
		s.pixelColour[2] = 0;
		return false;
	}
}

/*function to check intersections based on shadow ray*/
bool Sphere::checkShadow(Triangle::intersectInfo& s, Vec3& shadowRay) {
	
	float A = s.dir.dot(s.dir);
	float B = s.dir.dot(shadowRay) * 2;
	float C = shadowRay.dot(shadowRay) - pow(sphereRadius, 2);

	//compute the discriminant
	float discriminant = pow(B, 2) - (4 * A * C);

	//if the discriminant is greater than zero
	if (discriminant > 0) {
		//find roots t1 and t2
		float t1 = (-B - sqrt(discriminant)) / (2 * A);
		float t2 = (-B + sqrt(discriminant)) / (2 * A);

		//determine which one is the real intersection point
		float t = std::min(t1, t2);

		if (t > 0) {
			return true;
		}
	}
	else {
		return false;
	}
}



