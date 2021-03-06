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
        size_t size() {return v.size();}
        void add(std::shared_ptr<IHittable> object);
        virtual bool hit(const Ray &ray, double t_min, double t_max, HitRecord& record) const;
        ~Scene();
    };
}