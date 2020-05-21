#include <porto/camera.h>
#include <porto/vec3.h>
#include <math.h>

void porto::Camera::setup(double vfov, double aspect)
{
    double theta = vfov*M_PI/180;
    double half_height = tan(theta/2);
    double half_width = aspect * half_height;
    lower_left_corner = Vec3(-half_width, -half_height, 1.0);
    horizontal = Vec3(2*half_width, 0.0, 0.0);
    vertical = Vec3(0.0, 2*half_height, 0.0);
    origin = Vec3(0.0, 0.0, 0.0);
    this->vfov = vfov;
    this->aspect = aspect;
}


porto::Vec3 porto::Camera::mult(Vec3 A, Vec3 B, Vec3 C, Vec3 D)//[A B C]*[D] = [res]
{
    Vec3 res(D.x*A.x + D.y*B.x + D.z*C.x, D.x*A.y + D.y*B.y + D.z*C.y, D.x*A.z + D.y*B.z + D.z*C.z);
    res.normalize();
    res*=D.length();
    return res;
}

void porto::Camera::move(Vec3 orig, Vec3 hor, Vec3 ver, Vec3 nor)
{
    hor.normalize();
    ver.normalize();
    nor.normalize();

    horizontal = mult(hor, ver, nor, horizontal);
    vertical = mult(hor, ver, nor, vertical);
    lower_left_corner = mult(hor, ver, nor, lower_left_corner);
    lower_left_corner += orig;
    origin = orig;
}

porto::Camera::Camera(double vfov = 100, double width = 1920, double height = 1080, int nx = 1920, int ny = 1080, int ns = 100, int depth = 10,
    std::string filename = std::string("ex.ppm"), Vec3 orig = Vec3(0, 0, 0),
    Vec3 hor = Vec3(1, 0, 0), Vec3 ver = Vec3(0, 1, 0)) 
    : nx{nx}, ny{ny}, ns{ns}, depth{depth}, filename{filename}
{
    double aspect = width / height;
    setup(vfov, aspect);
    Vec3 nor = cross(hor, ver);
    ver = cross(nor, hor);
    move(orig, hor, ver, nor);
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