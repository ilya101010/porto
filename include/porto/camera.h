#pragma once

#include <porto/ray.h>

namespace porto
{
	class Camera {
	private:
		Vec3 origin;
		Vec3 lower_left_corner;
		Vec3 horizontal;
		Vec3 vertical;
		double vfov, aspect;
		void setup(double vfov, double aspect);
		int nx, ny;
		int ns, depth;
		std::string filename;
		Vec3 mult(Vec3 A, Vec3 B, Vec3 C, Vec3 D);//[A B C]*[D] = [res]
		void move(Vec3 orig = Vec3(0, 0, 0), Vec3 hor = Vec3(1, 0, 0), Vec3 ver = Vec3(0, 1, 0), Vec3 nor = Vec3(0, 0, 1));
	public:
		int getnx() {return nx;}
		int getny() {return ny;}
		int getns() {return ns;}
		int getdepth() {return depth;}
		std::string getfilename() {return filename;}
		//Camera();
		//Camera(double vfov, double aspect, int nx, int ny, std::string filename);
		Camera(double vfov, double width, double height, int nx, int ny, int ns, int depth, std::string filename, Vec3 orig, Vec3 hor, Vec3 ver);
		Ray getRay(double u, double v);
		void setVfov(double vfov);
		double getVfov();
		void setAspect(double aspect);
		double getAspect();
	};
}