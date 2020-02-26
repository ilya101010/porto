#include <porto/vec3.h>
#include <porto/ray.h>
#include <porto/sphere.h>
#include <porto/ihittable.h>
#include <porto/scene.h>
#include <iostream>
#include <cfloat>
namespace p = porto;

const float MAXF = FLT_MAX;

p::Sphere s(0,0,-1,0.5), s1(0.25,0,-1,0.5);
p::Scene scene;


p::Vec3 color(const p::Ray &r)
{
    p::HitRecord hr;
    if(scene.hit(r, 0, MAXF, hr))
    {
        float t = hr.t;
        return 0.5*p::Vec3(hr.normal.x+1, hr.normal.y+1, hr.normal.z+1);
    }
    float t = 0.5*(r.dir().y + 1.0);
    return (1.0-t)*p::Vec3(1.0, 1.0, 1.0) + t*p::Vec3(0.5, 0.7, 1.0);
}

int main()
{
    int nx = 800;
    int ny = 600;
    scene.add(&s);
    scene.add(&s1);
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    p::Vec3 lower_left_corner(-2.0, -1.5, -1.0);
    p::Vec3 horizontal(4.0, 0.0, 0.0);
    p::Vec3 vertical(0.0, 3.0, 0.0);
    p::Vec3 origin(0.0, 0.0, 0.0);
    for(int j = ny-1; j >= 0; j--)
    {
        for (int i = 0; i<nx; i++)
        {
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);
            p::Ray r(origin, lower_left_corner + u*horizontal + v*vertical);
            p::Vec3 col = color(r);
            int ir = int(255.99*col.r);
            int ig = int(255.99*col.g);
            int ib = int(255.99*col.b);
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}