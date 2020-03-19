#include <porto/scene.h>
#include <porto/ihittable.h>

porto::Scene* porto::Scene::clone() const{
    auto sc = new Scene();
    for(size_t i = 0; i < v.size(); ++i)
        sc->add(*v[i]);
    return sc;
}

bool porto::Scene::hit
    (const Ray &ray, float t_min, float t_max, HitRecord& record) const
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


void porto::Scene::add(IHittable &object)
{
    v.push_back(object.clone());
}

porto::Scene::Scene() {}

porto::Scene::~Scene(){
    for(size_t i = 0; i < v.size(); ++i)
        delete v[i];
}