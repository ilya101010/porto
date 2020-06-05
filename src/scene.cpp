#include <porto/scene.h>
#include <porto/ihittable.h>
#include <memory>
#include <iostream>

bool porto::Scene::hit
    (const Ray &ray, double t_min, double t_max, HitRecord& record) const
{
    // TODO: BVH
    bool hitAnything = false;
    HitRecord r, r_min;
    for(size_t i = 0; i<v.size(); i++)
    {
        if(v[i]->hit(ray, t_min, t_max, r) && (!hitAnything || r.t < r_min.t))
        {
            r_min = r;
            hitAnything = true;
        }
    }

    if(hitAnything)
        record = r_min;

    return hitAnything;
}


void porto::Scene::add(std::shared_ptr<IHittable> object)
{
    v.push_back(object);
}

porto::Scene::Scene() {}

porto::Scene::~Scene(){

}