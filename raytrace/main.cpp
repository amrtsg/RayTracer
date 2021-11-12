#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <iostream>
#include <Triangle.h>
#include <Sphere.h>
#include <Lights.h>
#include <Plane.h>
#include "Image.h"
#include <random>

using namespace std;

//Data types
typedef float Scalar;
typedef Eigen::Matrix<Scalar, 3, 1> Vec3;
typedef Eigen::Matrix<Scalar, 2, 1> Vec2;
typedef	unsigned char uchar;

int hsamples = 4;
int vsamples = 4;
Image image = Image(500, 500);
Colour triangleAmbient = Colour(150, 150, 150); //100, 100, 100

//bounding the channel wise pixel color between 0 to 255
uchar Clamp(int color)
{
	if (color < 0) return 0;
	if (color >= 255) return 255;
	return color;
}

/*Generate random spheres and push to sphere array*/
void createRandomStars(vector<Sphere>& s) {
	random_device rd;
	default_random_engine generator(rd()); // rd() provides a random seed
	uniform_real_distribution<double> x(-5, 5);
	uniform_real_distribution<double> y(3, 12);
	uniform_real_distribution<double> radius(0.01, 0.1);

	//Generate random stars with random position
	for (int i = 0; i <= 20; i++) {
		double randX = x(generator);
		double randY = y(generator);
		double randR = radius(generator);
		s.push_back(Sphere(Vec3(randX, randY, -13), randR, Colour(255, 255, 255)));
	}
	Sphere planet1 = Sphere(/*center*/Vec3(-2, 4, -12), /*radius*/1, Colour(66, 0, 66));
	Sphere planet2 = Sphere(Vec3(2, 3, -12), 0.7, Colour(0, 66, 0));
	Sphere planet3 = Sphere(Vec3(0, -0.5, -3), 1, Colour(0, 150, 210));
	s.push_back(planet1);
	s.push_back(planet2);
	s.push_back(planet3);
}

/*Generate triangles and push to triangle array*/
void createTriangles(vector<Triangle>& triangles) {
	//floor
	Triangle t1 = Triangle(Vec3(1, -1, -1)/*bottom*/, Vec3(2, -1, -5)/*top right*/, Vec3(-2, -1, -5)/*top left*/, triangleAmbient); //RIGHT TRIANGLE
	Triangle t2 = Triangle(Vec3(-2, -1, -5)/*top*/, Vec3(-1, -1, -1)/*bottom left*/, Vec3(1, -1, -1)/*bottom right*/, triangleAmbient); //LEFT TRIANGLE
	//left wall
	Triangle t3 = Triangle(Vec3(-1, -1, -1)/*bottom left*/, Vec3(-2, -1, -5)/*bottom right*/, Vec3(-1, 1, -1)/*top*/, triangleAmbient); //LEFT TRIANGLE
	Triangle t4 = Triangle(Vec3(-1, 1, -1)/*bottom right*/, Vec3(-2, -1, -5)/*top*/, Vec3(-2, 5, -5)/*bottom left*/, triangleAmbient); //RIGHT TRIANGLE
	//right wall
	Triangle t5 = Triangle(Vec3(1, -1, -1)/*bottom right*/, Vec3(2, -1, -5)/*bottom left*/, Vec3(1, 1, -1)/*top*/, triangleAmbient); //RIGHT TRIANGLE
	Triangle t6 = Triangle(Vec3(2, -1, -5)/*bottom*/, Vec3(2, 5, -5)/*top left*/, Vec3(1, 1, -1)/*top right*/, triangleAmbient); //LEFT TRIANGLE
	//back wall
	Triangle t7 = Triangle(Vec3(2, -1, -5)/*bottom*/, Vec3(2, 5, -5)/*top right*/, Vec3(-2, 5, -5)/*top left*/, Colour(100, 40, 0)); //RIGHT TRIANGLE
	Triangle t8 = Triangle(Vec3(2, -1, -5)/*bottom right*/, Vec3(-2, 5, -5)/*top*/, Vec3(-2, -1, -5)/*bottom left*/, Colour(100, 40, 0)); //LEFT TRIANGLE
	triangles.push_back(t1);
	triangles.push_back(t2);
	triangles.push_back(t3);
	triangles.push_back(t4);
	triangles.push_back(t5);
	triangles.push_back(t6);
	triangles.push_back(t7);
	triangles.push_back(t8);

}

/*Method to find pixel position*/
Vec3 findPixelPos(int col, int row, int p, int q) {
	Vec3 llc = Vec3(-1, -1, -1); //lower left corner
	Vec3 urc = Vec3(1, 1, -1); //upper right corner
	int width = urc(0) - llc(0);
	int height = urc(1) - llc(1);
	Vec2 pixelUV = Vec2((float)width / image.cols, (float)height / image.rows);
	float r = ((double)rand() / (RAND_MAX));
	float u;
	float v;
	float z = -1;
	u = (llc(0) + pixelUV(0) * (col + (p + r) / hsamples));
	v = (llc(1) + 2 - pixelUV(1) * (row + (q + r) / vsamples));
	return Vec3(u, v, z);
}

int main(int, char**) {
	vector<Sphere> stars;
	vector<Sphere> planets;
	vector<Triangle> walls;
	createRandomStars(stars);
	createTriangles(walls);
	

	//Main loop, goes through each pixel.
	for (int row = 0; row < image.rows; ++row) {
		for (int col = 0; col < image.cols; ++col) {

			Vec3 dir;
			Vec3 shadowRay;
			vector<Triangle::intersectInfo> intersections;
			Triangle::intersectInfo closest;
			Triangle::intersectInfo s;
			Vec3 pixelColor(0, 0, 0);

			//loops for super sampling
			for (int p = 0; p < hsamples; p++) {
				for (int q = 0; q < vsamples; q++) {
				
					//Find pixelPos.
					Vec3 pixelPos = findPixelPos(col, row, p, q);
					s.dir = pixelPos - CameraPoint;
					//Start triangle intersections
					for (int i = 0; i < walls.size(); i++) {
						if (walls[i].TriangleIntersect(s)) { //if intersection found, add to array of intersections
							intersections.push_back(s);
						}
					}
					//Start stars intersection
					for (int i = 0; i < stars.size(); i++) { //if intersection found, add to array of intersections
						if (stars[i].SphereIntersect(s)) {
							intersections.push_back(s);
						}
					}
					//find the object with the lowest T value.
					float tMin = 1000;
					for (int i = 0; i < intersections.size(); i++) {
						if (tMin > intersections[i].tVal) {
							closest = intersections[i];
						}
					}
					//define shadow ray
					Vec3 shadowRay = (LightSource - closest.POI + eps);
	
					//pass shadow ray to sphere checkShadow and check intersection
					bool isIntersect = false;
					for (int i = 0; i < stars.size(); i++) {
						if (stars[i].checkShadow(s, shadowRay)) {
							isIntersect = true;
						}
					}

					//if shadow ray intersects, make the pixel color darker
					if (isIntersect && s.amb == triangleAmbient) {
						pixelColor[0] += closest.pixelColour[0]/1.2;
						pixelColor[1] += closest.pixelColour[1]/1.2;
						pixelColor[2] += closest.pixelColour[2]/1.2;
					}
					else {
						pixelColor[0] += closest.pixelColour[0];
						pixelColor[1] += closest.pixelColour[1];
						pixelColor[2] += closest.pixelColour[2];
					}
				}
			}
			//Average the sample colors for final color.
			pixelColor[0] = Clamp(pixelColor[0] / (hsamples * vsamples));
			pixelColor[1] = Clamp(pixelColor[1] / (hsamples * vsamples));
			pixelColor[2] = Clamp(pixelColor[2] / (hsamples * vsamples));


			image(row, col) = Colour(pixelColor[0], pixelColor[1], pixelColor[2]);
		}
	}

	//Display image
	image.save("./result.png");
	image.display();

	return EXIT_SUCCESS;
}

