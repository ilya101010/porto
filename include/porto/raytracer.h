#pragma once

#include <porto/camera.h>
#include <porto/scene.h>
#include <porto/vec3.h>

namespace porto
{
    class Raytracer
    {
        int width;
        int height;
    public:
        Camera cam;
        Scene scene;
        Raytracer(int width = 800, int height = 600, double vfov = 90,
                Vec3 origin = Vec3(0,0,0));
        ~Raytracer();
        Vec3 getPixel(int x, int y);
    };
}