#pragma once

#include <porto/ihittable.h>
#include <vector>

namespace porto
{
    class Scene: public IHittable // TODO: BVH
    {
    private:
        std::vector<IHittable*> v;
    public:
        Scene();
        void add(IHittable *object);
        virtual bool hit(const Ray &ray, float t_min, float t_max, HitRecord& record) const;
    };
}