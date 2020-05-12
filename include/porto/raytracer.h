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
        std::shared_ptr<Camera> cam;
        std::shared_ptr<Scene> scene;
        Raytracer(int width = 800, int height = 600, double vfov = 90,
                Vec3 origin = Vec3(0,0,0));
        Raytracer(std::shared_ptr<Scene> scene, std::shared_ptr<Camera> cam);
        ~Raytracer();
        Vec3 getPixel(int x, int y);
    };
}