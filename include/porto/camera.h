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
		std::string filename;

	public:
		int getnx() {return nx;}
		int getny() {return ny;}
		std::string getfilename() {return filename;}
		//Camera();
		//Camera(double vfov, double aspect, int nx, int ny, std::string filename);
		Camera(double vfov, double width, double height, int nx, int ny, std::string filename);
		Ray getRay(double u, double v);
		void setVfov(double vfov);
		double getVfov();
		void setAspect(double aspect);
		double getAspect();
	};
}