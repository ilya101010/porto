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
    for (int i=0; i<12; ++i)
    {
        json camera_json{
            {"origin", {my_random(-30, 30), my_random(-30, 30), my_random(-30, 30)}},
            {"ver", {my_random(-1, 1), my_random(-1, 1), my_random(-1, 1)}},
            {"hor", {my_random(-1, 1), my_random(-1, 1), my_random(-1, 1)}},
            {"nx", 500},
            {"ny", 500},
            {"vfov", 110},
            {"ns", 20},
            {"depth", 10},
            {"cam_filename", (string("pictures/dir_3/make_2_conf_3_")+to_string(i+1)+string(".ppm"))}
        };
        world_json["cameras"].push_back(camera_json);
    }
    for(double i=0; i<40; i+=1) 
    {
        json sph_i{
            {"sphere_Lambertian", 
                {
                    {"o", {my_random(-20, 20), my_random(-20, 20), my_random(-20, 20)}},
                    {"material", {my_random(),my_random(), my_random()}},
                    {"r", sqrt(sqrt(my_random(2, 100)))}
                }
            }
        };
        world_json["scene"].push_back(sph_i);
    }
    out<<world_json;
    out.close();
}

int main(){
    write_hard_configs("make_2_config_3_made.json");
}