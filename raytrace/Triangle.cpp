#include "Triangle.h"
#include "Sphere.h"
#include "Lights.h"
#include <iostream>

bool Triangle::TriangleIntersect(Triangle::intersectInfo& s) {
	Vec3 tNormal = normal_;
	tNormal.normalize();
	Scalar t = (float)(vertex1_ - CameraPoint).dot(tNormal) / s.dir.dot(tNormal);
	s.POI = CameraPoint + (t * s.dir);
	Vec3 baryCoords = BaryCentric(s.POI);

	if (fabs(baryCoords[0] + baryCoords[1] + baryCoords[2]) - 1 < 0.00001 &&
		baryCoords[0] > 0 && baryCoords[0] < 1 &&
		baryCoords[1] > 0 &&
		baryCoords[1] < 1 &&
		baryCoords[2] > 0 &&
		baryCoords[2] < 1) {
		//s.POI = CameraPoint + (s.dir * t);
		Vec3 LightVector = LightSource - s.POI;
		LightVector.normalize();

		Vec3 viewVec = CameraPoint - s.POI;
		viewVec.normalize();

		float dotNL = tNormal.dot(LightVector);
		Vec3 h = (viewVec + LightVector) / ((viewVec + LightVector)).norm();

		float diffuseTerm = LightVector.dot(tNormal);
		float specularTerm = (pow(tNormal.dot(h), 128));

		if (diffuseTerm < 0) diffuseTerm = 0;
		if (specularTerm < 0) specularTerm = 0;
		//if yes, add the sample color to pixelColour for averaging at the end. Use the object colour. 
		s.pixelColour[0] = (ambient[0] + (triangleDiffuse[0] * diffuseTerm));
		s.pixelColour[1] = (ambient[1] + (triangleDiffuse[1] * diffuseTerm));
		s.pixelColour[2] = (ambient[2] + (triangleDiffuse[2] * diffuseTerm));
		s.tVal = t;
		s.amb = ambient;
		return true;
	}
	else {
		s.pixelColour[0] = 0;
		s.pixelColour[1] = 0;
		s.pixelColour[2] = 0;
		return false;
	}
}

/*compute barycentric coordinates*/
Vec3 Triangle::BaryCentric(const Vec3& point)
{
	float alpha;
	float beta;
	float gamma;
	Vec3 nA;
	Vec3 nB;
	Vec3 nC;

	Vec3 n = normal_;
	nA = (vertex3_ - vertex2_).cross(point - vertex2_);
	nB = (vertex1_ - vertex3_).cross(point - vertex3_);
	nC = (vertex2_ - vertex1_).cross(point - vertex1_);

	float sqrdNorm = n.squaredNorm();

	alpha = (n.dot(nA)) / sqrdNorm;
	beta = (n.dot(nB)) / sqrdNorm;
	gamma = (n.dot(nC)) / sqrdNorm;

	return Vec3(alpha, beta, gamma);
}


Vec3 Triangle::ComputeNormal(const Vec3& p1, const Vec3& p2, const Vec3& p3)
{
	Vec3 v12 = p2 - p1;
	Vec3 v13 = p3 - p1;
	return v12.cross(v13);
}




