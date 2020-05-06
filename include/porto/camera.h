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

	public:
		Camera();
		Camera(double vfov, double aspect);
		Camera(double vfov, double width, double height);
		Ray getRay(double u, double v);
		void setVfov(double vfov);
		double getVfov();
		void setAspect(double aspect);
		double getAspect();
	};
}