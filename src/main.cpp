#include <porto/vec3.h>
#include <iostream>

namespace p = porto;

int main()
{
    int nx = 200;
    int ny = 200;
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    for(int j = ny-1; j >= 0; j--)
    {
        for (int i = 0; i<nx; i++)
        {
            p::Vec3 col(float(i) / float(nx), float(j) / float(ny), 0.2);
            int ir = int(255.99*col.r);
            int ig = int(255.99*col.g);
            int ib = int(255.99*col.b);
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}