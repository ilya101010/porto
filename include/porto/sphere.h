#pragma once
#include <porto/vec3.h>
#include <porto/ray.h>
#include <porto/ihittable.h>
#include <porto/material.h>


namespace porto
{
    class Sphere: public IHittable
    {
    public:
        Vec3 c;
        double r;

        Sphere(const Vec3 &center, double radius) : c{center}, r{radius} {}
        Sphere(double x, double y, double z, double radius) : c{x,y,z}, r{radius} {}

        virtual bool hit(const Ray &ray, double t_min, double t_max, HitRecord& record) const;
        virtual Sphere* clone() const;
        ~Sphere() {}
    };
}