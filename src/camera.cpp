#include <porto/camera.h>
#include <porto/vec3.h>
#include <math.h>

void porto::Camera::setup(float vfov, float aspect)
{
    float theta = vfov*M_PI/180;
    float half_height = tan(theta/2);
    float half_width = aspect * half_height;
    lower_left_corner = Vec3(-half_width, -half_height, -1.0);
    horizontal = Vec3(2*half_width, 0.0, 0.0);
    vertical = Vec3(0.0, 2*half_height, 0.0);
    origin = Vec3(0.0, 0.0, 0.0);
    this->vfov = vfov;
    this->aspect = aspect;
}

porto::Camera::Camera(float vfov, float aspect)
{
    setup(vfov, aspect);
}

porto::Camera::Camera(float vfov, float width, float height)
{
    float aspect = width / height;
    setup(vfov, aspect);
}

porto::Ray porto::Camera::getRay(float u, float v) {
    return porto::Ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
    // to add diafragma add to origin random number
}

void porto::Camera::setVfov(float vfov)
{
    setup(vfov, aspect);
}

float porto::Camera::getVfov()
{
    return vfov;
}

void porto::Camera::setAspect(float aspect)
{
    setup(vfov, aspect);
}

float porto::Camera::getAspect()
{
    return aspect;
}