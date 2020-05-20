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

    /*void examples_working_with_json_nothing_more(){
        json j;
        j.push_back("foo");
        j.push_back(1);
        j.push_back(true);

        // also use emplace_back
        j.emplace_back(1.78);

        // iterate the array
        for (json::iterator it = j.begin(); it != j.end(); ++it) {
        std::cout << *it << '\n'; 
        }

        // range-based for
        for (auto& element : j) {
        std::cout << element << '\n';
        }

        // getter/setter
        const auto tmp = j[0].get<std::string>();
        j[1] = 42;
        bool foo = j.at(2);

        // comparison
        j == "[\"foo\", 42, true]"_json;  // true

        // other stuff
        j.size();     // 3 entries
        j.empty();    // false
        j.type();     // json::value_t::array
        j.clear();    // the array is empty again

        // convenience type checkers
        j.is_null();
        j.is_boolean();
        j.is_number();
        j.is_object();
        j.is_array();
        j.is_string();

        // create an object
        json o;
        o["foo"] = 23;
        o["bar"] = false;
        o["baz"] = 3.141;

        // also use emplace
        o.emplace("weather", "sunny");

        json ff;
        ff.emplace("my", 3);
        ff["camera"] = o; 
        o["foo"] = 0;
        std::cout << "\nOMMMMG\n" << ff << std::endl;

        // special iterator member functions for objects
        for (json::iterator it = o.begin(); it != o.end(); ++it) {
        std::cout << it.key() << " : " << it.value() << "\n";
        }

        // the same code as range for
        for (auto& el : o.items()) {
        std::cout << el.key() << " : " << el.value() << "\n";
        }

        // even easier with structured bindings (C++17)
        for (auto& [key, value] : o.items()) {
        std::cout << key << " : " << value << "\n";
        }
        
        // find an entry
        if (o.find("foo") != o.end()) {
        // there is an entry with key "foo"
        }

        // or simpler using count()
        int foo_present = o.count("foo"); // 1
        int fob_present = o.count("fob"); // 0

        // delete an entry
        o.erase("foo");
    }*/

    void write_hard_configs(const char * filename)
    {
        std::ofstream out(filename);
        json world_json{
            {"cameras", json::array()},
            {"scene", json::array()}
        };
        json camera_json{
            {"origin", {0, 0, 0}},
            {"normale", {0, 0, 1}},
            {"nx", 1000},
            {"ny", 1000},
            {"vfov", 100},
            {"cam_filename", "pictures/ex_1.ppm"}
        };
        world_json["cameras"].push_back(camera_json);
        
        for(double a = 0; a<5;a++)
            for(double b = 0; b<5; b++) 
            {
                json sph_i{
                    {"sphere_Lambertian", 
                        {
                            {"o", {(-5+2*a),(-5+2*b), 5 + (a+b)/2}},
                            {"material", {random_double(),random_double(), random_double()}},
                            {"r", 0.9}
                        }
                    }
                };
                world_json["scene"].push_back(sph_i);
            }
        out<<world_json;
        out.close();
    }

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
    
            std::vector<double> normale, origin;
            double vfov; int nx, ny;
            std::string cam_filename;
            EXTRACT(vfov, value);
            EXTRACT(nx, value);
            EXTRACT(ny, value);
            EXTRACT(normale, value);
            EXTRACT(origin, value);
            EXTRACT(cam_filename, value);
            //std::cout << nx << ' ' << ny << ' ' << vfov << '\n';
            cameras.push_back(std::make_shared<Camera>(vfov, (double) nx, (double) ny, nx, ny, cam_filename));
    
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