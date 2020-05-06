#pragma once
#include <porto/vec3.h>

namespace porto
{
    class Ray
    {
        Vec3 _src, _dir;
    public:
        Ray(Vec3 source, Vec3 direction) : _src{source}, _dir{direction} {
            _dir.normalize();
        }

        inline Vec3 src() const { return _src; }
        inline Vec3 dir() const { return _dir; } 
        inline Vec3 point_at_parameter(double t) const { return _src + t*_dir; }
    };
}