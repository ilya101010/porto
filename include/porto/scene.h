#pragma once

#include <porto/ihittable.h>
#include <vector>
#include <memory>

namespace porto
{
    class Scene: public IHittable // TODO: BVH
    {
    private:
        std::vector<std::shared_ptr<IHittable> > v;
    public:
        Scene();
        void add(std::shared_ptr<IHittable> object);
        virtual bool hit(const Ray &ray, float t_min, float t_max, HitRecord& record) const;
        virtual Scene* clone() const;
        ~Scene();
    };
}