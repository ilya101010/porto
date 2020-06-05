#include "../include/json.hpp"
#include <functional>
#include <random>
#include <limits>
#include <fstream>
#include <cmath>
#include <string>

using json = nlohmann::json;
using namespace std;

double random_double(double l=0, double r=1)
{
    return (double) rand()/RAND_MAX;
    /*static std::uniform_real_distribution<double> distribution(l, r);
    static std::mt19937 generator;
    static std::function<double()> rand_generator =
        std::bind(distribution, generator);￼
    return rand_generator();*/
}

double my_random(double l=0, double r=1){
    return (random_double()-0.5)*(r-l)+(r+l)/2;
}

void write_hard_configs(const char * filename)
{
    std::ofstream out(filename);
    json world_json{
        {"cameras", json::array()},
        {"scene", json::array()}
    };
    {
        json camera_json{
            {"origin", {0, 0, -10}},
            {"ver", {0, 1, 0}},
            {"hor", {1, 0, 0}},
            {"nx", 500},
            {"ny", 500},
            {"vfov", 110},
            {"ns", 50},
            {"depth", 10},
            {"cam_filename", (string("pictures/dir_8/make_2_conf_3_")+to_string(1)+string(".ppm"))}
        };
        world_json["cameras"].push_back(camera_json);
    }
    for (int i=1; i<20; ++i)
    {
        json camera_json{
            {"origin", {my_random(-12, 12), my_random(-12, 12), -5}},
            {"ver", {my_random(-1, 1), my_random(-1, 1), my_random(-1, 1)}},
            {"hor", {my_random(-1, 1), my_random(-1, 1), my_random(-1, 1)}},
            {"nx", 200},
            {"ny", 200},
            {"vfov", 110},
            {"ns", 20},
            {"depth", 10},
            {"cam_filename", (string("pictures/dir_8/make_2_conf_3_")+to_string(i+1)+string(".ppm"))}
        };
        world_json["cameras"].push_back(camera_json);
    }
    double z = 1, phi = 1, k = 3, r = z*z, x, y;
    for(double i=0; i<100; i+=1) 
    {
        r = z*z;
        phi += k/r;
        //k+=(double)1/20;
        x = r * sin(phi);
        y = r * cos(phi);
        z += (double)1/5/r;
        json sph_i{
            {"sphere_Lambertian", 
                {
                    {"o", {x + my_random(-0.1,0.1), y + my_random(-0.1,0.1), z + my_random(-0.1,0.1)}},
                    {"material", {my_random(),my_random(), my_random()}},
                    {"r", sqrt(sqrt(my_random(2, 5)))}
                }
            }
        };
        world_json["scene"].push_back(sph_i);
    }
    out<<world_json;
    out.close();
}

int main(){
    write_hard_configs("make_2_config_8_made.json");
}