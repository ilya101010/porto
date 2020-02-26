#include <porto/scene.h>
#include <porto/ihittable.h>

bool porto::Scene::hit
    (const Ray &ray, float t_min, float t_max, HitRecord& record) const
{
    // TODO: BVH
    bool hitAnything = false;
    HitRecord r, r_min;
    for(int i = 0; i<v.size(); i++)
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

void porto::Scene::add(IHittable *object)
{
    v.push_back(object);
}

porto::Scene::Scene() {}