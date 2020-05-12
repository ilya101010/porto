#include <porto/camera.h>
#include <porto/vec3.h>
#include <math.h>

void porto::Camera::setup(double vfov, double aspect)
{
    double theta = vfov*M_PI/180;
    double half_height = tan(theta/2);
    double half_width = aspect * half_height;
    lower_left_corner = Vec3(-half_width, -half_height, -1.0);
    horizontal = Vec3(2*half_width, 0.0, 0.0);
    vertical = Vec3(0.0, 2*half_height, 0.0);
    origin = Vec3(0.0, 0.0, 0.0);
    this->vfov = vfov;
    this->aspect = aspect;
}

porto::Camera::Camera(double vfov, double aspect, int nx = 1920, int ny = 1080) : nx{nx}, ny{ny}
{
    setup(vfov, aspect);
}

porto::Camera::Camera(double vfov, double width, double height, int nx = 1920, int ny = 1080) : nx{nx}, ny{ny}
{
    double aspect = width / height;
    setup(vfov, aspect);
}

porto::Ray porto::Camera::getRay(double u, double v) {
    return porto::Ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
    // to add diafragma add to origin random number
}

void porto::Camera::setVfov(double vfov)
{
    setup(vfov, aspect);
}

double porto::Camera::getVfov()
{
    return vfov;
}

void porto::Camera::setAspect(double aspect)
{
    setup(vfov, aspect);
}

double porto::Camera::getAspect()
{
    return aspect;
}