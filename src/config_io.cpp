#include <porto/config_io.h>

#include <json.hpp>
#include <porto/raytracer.h>
#include <porto/vec3.h>
#include <porto/ray.h>
#include <porto/sphere.h>
#include <porto/ihittable.h>
#include <porto/scene.h>
#include <porto/camera.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <porto/material.h>

namespace porto
{
    using json = nlohmann::json;

    /*json world_json{
        {"cameras", json::array()},
        {"scene", json::array()}
    };
    json camera_json{
        {"origin", {-2, -2, -2}},
        {"ver", {1, 1, 0}},
        {"hor", {1, 0, 1}},
        {"nx", 192*2},
        {"ny", 108*2},
        {"vfov", 100},
        {"ns", 100},
        {"depth", 10},
        {"cam_filename", "pictures/make_conf_6.ppm"}
    };
    json sph_i{
        {"sphere_Lambertian", 
            {
                {"o", {(i/4)*1.2*(sin(i*20/180*3.1415)) + my_random(-0.1, 0.1) + 1,(i/5)*0.9*cos(i*20/180*3.1415) + my_random(-0.1, 0.1), 7 + my_random(-1, 1)}},
                {"material", {my_random(),my_random(), my_random()}},
                {"r", sqrt(my_random(0.3, 0.9)*i/6)}
            }
        }
    };*/

    #define EXTRACT(x, J) x = J[#x].get< decltype(x) >()

    void read_configs(std::vector< std::shared_ptr < porto::Camera > > &cameras, std::shared_ptr < Scene > & scene, std::istream & in)
    {
        //std::ifstream in("conf.json");
        json world_json;
        in >> world_json;
        //std::cout<<world_json;
        for(auto& [key, value] : world_json["cameras"].items())
        {
            //std::cout << "\nCAMERA\n" << key << ' ' << value << "\n";
    
            std::vector<double> hor, ver, origin;
            double vfov; int nx, ny, ns, depth;
            std::string cam_filename;
            EXTRACT(vfov, value);
            EXTRACT(nx, value);
            EXTRACT(ny, value);
            EXTRACT(ns, value);
            EXTRACT(depth, value);
            EXTRACT(hor, value);
            EXTRACT(ver, value);
            EXTRACT(origin, value);
            EXTRACT(cam_filename, value);
            //std::cout << nx << ' ' << ny << ' ' << vfov << ' ' <<cam_filename<< '\n';
            cameras.push_back(std::make_shared<Camera>(vfov, (double) nx, (double) ny, nx, ny, ns, depth, cam_filename,
             Vec3(origin[0], origin[1], origin[2]), Vec3(hor[0], hor[1], hor[2]), Vec3(ver[0], ver[1], ver[2])));
    
        }
        scene = std::make_shared<Scene>();
        for(auto& [key, value] : world_json["scene"].items())
        {
            //std::cout << key << " : " << value << "\n";
            for (auto & it : value.items())
                if (it.key() == "sphere_Lambertian")
                {   
                    std::vector<double> o, material;
                    double r;
                    EXTRACT(o, it.value());
                    EXTRACT(r, it.value());
                    EXTRACT(material, it.value());
                    //std::cout<<"shp\n"<< o[0] << ' ' << o[1] << ' ' << o[2] << ' ' << r << '\n';
                    //auto sph = std::make_shared<Sphere>(o[0], o[1], o[2], r);
                    //std::cout << "still alive\n";
                    scene->add(std::make_shared<Sphere>(Vec3(o[0], o[1], o[2]), r, std::make_shared<Lambertian>(Vec3(material[0], material[1], material[2]))));
                    //std::cout << "still alive\n";
                    //std::cout << scene->size() << '\n';
                }
        }
        //in.close();
    }
    
}