#pragma once
#include <porto/raytracer.h>

namespace porto {
    class MPI_unit 
    {
        const int Tag = 0;
        const int root = 0;
        int rank = 0, commSize = 0;
        void fun(Raytracer& engine, double* arr, int start, int count, int nx);
        void ppm(const double * arr, const int nx, const int ny, const char * filename);
    public:
        int getrank() const;
        int getcommSize() const;
        MPI_unit(int argc, char *argv[]);
        ~MPI_unit();
        void run(Raytracer & engine);
    };
}