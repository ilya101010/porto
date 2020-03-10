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
		float vfov, aspect;
		void setup(float vfov, float aspect);

	public:
		Camera();
		Camera(float vfov, float aspect);
		Camera(float vfov, float width, float height);
		Ray getRay(float u, float v);
		void setVfov(float vfov);
		float getVfov();
		void setAspect(float aspect);
		float getAspect();
	};
}