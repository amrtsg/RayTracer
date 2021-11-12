#pragma once
#include "Plane.h"

/*void Plane::PlaneIntersect(Vec3 CameraPoint, Vec3 LightSource, Image image, Colour ambient) {
	for (int row = 0; row < image.rows; ++row) {
		for (int col = 0; col < image.cols; ++col) {
			//COLORS
			Colour diffuse = Colour(255, 255, 255);

			//------------------------------------RENDER PLANE-------------------------------------------------------
			//Find the pixel position (PixelPos) for each row and col and then construct the vector PixelPos-Origin
			Vec3 llc = Vec3(-1, -1, -1); //lower left corner
			Vec3 urc = Vec3(1, 1, -1); //upper right corner
			int width = urc(0) - llc(0);
			int height = urc(1) - llc(1);
			Vec2 pixelUV = Vec2((float)width / image.cols, (float)height / image.rows);

			float u;
			float v;
			float z = -1;
			u = llc(0) + (pixelUV(0)) * (row + 0.5);
			v = llc(1) + (pixelUV(1)) * (col + 0.5);

			Vec3 PixelPos = Vec3(u, v, z); //create a 3d vector with uv, and z as -1

			//Ray-plane Intersection
			Vec3 dir = PixelPos - CameraPoint;
			Vec3 ray = (CameraPoint - planeCenter);
			Vec3 sub = CameraPoint - ray;

			float t = (sub.dot(planeNormal)) / (dir.dot(planeNormal));

			if (t > 0) {
				///TODO: Basic shading (Weightage: 20%)                  
				Vec3 POI = CameraPoint + (dir * t);//POI = CameraPoint + direction*t
				Vec3 Normal = POI - planeCenter;
				Normal.normalize();
				Vec3 LightVector = LightSource - POI;//LightVec = lightsource - POI
				LightVector.normalize();
				float diffuseTerm = LightVector.dot(Normal);
				if (diffuseTerm < 0) diffuseTerm = 0;

				Colour colour(0, 0, 0); //The ambient base
				colour[0] = Clamp(ambient[0] + diffuse[0] * diffuseTerm);
				colour[1] = Clamp(ambient[1] + diffuse[1] * diffuseTerm);
				colour[2] = Clamp(ambient[2] + diffuse[2] * diffuseTerm);
				image(row, col) = colour;
			}
			//-----------------------------------END OF RENDER PLANE-----------------------------------------------
		}
	}
}*/




