#include <porto/vec3.h>
#include <porto/ray.h>
#include <porto/sphere.h>
#include <porto/ihittable.h>
#include <porto/scene.h>
#include <porto/camera.h>
#include <iostream>
#include <functional>
#include <random>
#include <cstdlib>
#include <porto/raytracer.h>
#include <mpi.h>
#include <cstdio>
#include <unistd.h>
namespace p = porto;

p::Sphere s(0,0,-2,1), s1(0,-100.6,-2,100);//, s2(-1,0.4,-0.7,0.7);

void fun(p::Raytracer& engine, double* arr, int start, int count, int nx){
	for (int j = start, ind = 0; j < start + count; ++j)
		{
			for (int i = 0; i < nx; ++i)
			{
				p::Vec3 col = engine.getPixel(i, j);
				arr[ind] = col.r;
				arr[ind + 1] = col.g;
				arr[ind + 2] = col.b;
				ind += 3;
			}
		}
}

int main(int argc, char *argv[])
{
	//MPI
	int rank, commSize;
	const int Tag = 0;
	const int root = 0;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &commSize);
	
	//TRACE
	int nx = 500;
	int ny = 500;
	p::Raytracer engine{nx, ny, 90};
	//engine.scene.add(&s);
	for(double a = 0; a<5;a++)
		for(double b = 0; b<5; b++) 
		{
			auto sph = p::Sphere(double(-5+2*a), double(-5+2*b), -2-(a+b)/2, 0.9f);
			engine.scene.add(std::make_shared<p::Sphere>(sph));
		}
	//#pragma omp parallel for

	//MPI
	if (rank == root)
	{
		fprintf(stderr, "I'm root, commSize is %d\n", commSize);
		std::cout << "P3\n" << nx << " " << ny << "\n255\n";
		MPI_Status status;
		double * arr = new double [nx * ny * 3] {};
		int partSize = ny/commSize;
		int shift = ny%commSize;
		for (int i = root+1; i < commSize; ++i) 
		{
			int msg[2] {shift + partSize*i, partSize};
			fprintf(stderr, "I'm root, send to %d start %d count %d\n", i, msg[0], msg[1]);
			MPI_Send(msg, 2, MPI_INT, i, Tag, MPI_COMM_WORLD);
		}
		//TRACE
		fun(engine, arr, 0, partSize, nx);

		for (int i = root+1; i < commSize; ++i) 
		{
			MPI_Recv(arr + (shift + partSize*i) * nx * 3, partSize * nx * 3, MPI_FLOAT, i, Tag, MPI_COMM_WORLD, &status);
		}

		for(int j = ny-1; j >= 0; j--)
		{
			for (int i = 0; i<nx; i++)
			{
				const int ind = (j * nx + i) * 3;
				int ir = int(255.99*arr[ind]);
				int ig = int(255.99*arr[ind + 1]);
				int ib = int(255.99*arr[ind + 2]);
				std::cout << ir << " " << ig << " " << ib << "\n";
			}
		}
		delete[] arr;
	}
	else 
	{
		MPI_Status status;
		int msg[2];
		MPI_Recv(msg, 2, MPI_INT, root, Tag, MPI_COMM_WORLD, &status);
		//usleep(1000 + 100*rank);
		//fprintf(stderr, "I'm %d, start is %d, count is %d\n", rank, msg[0], msg[1]);
		int start = msg[0];
		int count = msg[1];
		double* arr = new double[count * nx * 3];
		fun(engine, arr, start, count, nx);
		MPI_Send(arr, count * nx * 3, MPI_FLOAT, root, Tag, MPI_COMM_WORLD);
		delete[] arr;
	}

	MPI_Finalize();
}