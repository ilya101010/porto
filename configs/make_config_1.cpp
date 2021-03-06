#include "../include/json.hpp"
#include <functional>
#include <random>
#include <limits>
#include <fstream>
#include <cmath>

using json = nlohmann::json;

double random_double(double l=0, double r=1)
{
    return (double) rand()/RAND_MAX;
    /*static std::uniform_real_distribution<double> distribution(l, r);
    static std::mt19937 generator;
    static std::function<double()> rand_generator =
        std::bind(distribution, generator);
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
            {"origin", {0, 0, 0}},
            {"ver", {0, 1, 0}},
            {"hor", {1, 0, 0}},
            {"nx", 500},
            {"ny", 500},
            {"vfov", 110},
            {"ns", 10},
            {"depth", 10},
            {"cam_filename", "pictures/make_2_conf_1_2.ppm"}
        };
        world_json["cameras"].push_back(camera_json);
    }
    for(double i=0; i<30; i+=1) 
    {
        json sph_i{
            {"sphere_Lambertian", 
                {
                    {"o", {(i/4)*(sin(i*20/180*3.1415)) + my_random(-0.1, 0.1) + 1,(i/4)*cos(i*20/180*3.1415) + my_random(-0.1, 0.1), 7 + my_random(-1, 1)}},
                    {"material", {my_random(),my_random(), my_random()}},
                    {"r", sqrt(my_random(0.3, 0.9)*i/6)}
                }
            }
        };
        world_json["scene"].push_back(sph_i);
    }
    out<<world_json;
    out.close();
}

int main(){
    write_hard_configs("make_2_config_1_made.json");
}