#pragma once
//#include <porto/vec3.h>
#include "vec3.h"

namespace porto
{
    class Ray
    {
        Vec3 src, dir;
    public:
        Ray(Vec3 source, Vec3 direction) : src{source}, dir{direction} {
            dir.normalize();
        }
        Vec3 src() { return src; }
        Vec3 dir() { return dir; } 
        Vec3 point_at_parameter(float t) { return src + t*dir; }
    }
}

