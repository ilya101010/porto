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

	if (rank == root)
	{
		//MPI root
		fprintf(stderr, "I'm root, commSize is %d\n", commSize);//print config information 
		MPI_Status status;
		double * arr = new double [nx * ny * 3] {};//line array with whole picture to fill
		int partSize = ny/commSize;//count_of_lines to each task
		int shift = ny%commSize;//remaining lines for distribution
		int *msg = new int[2* commSize];//distribution massive
		/*massive with start index on 2*i positions and
		 count of lines on 2*i+1 positions. 0 is root, 
		 i = 1..commSize-1 are clients*/
		for (int i = root; i < shift; ++i) {
			msg[2*i] = (partSize + 1) * i;
			msg[2*i + 1] = partSize + 1;
		} //clients with count_of_lines partSize+1 to distribute remainig lines
		for (int i = shift; i < commSize; ++i) {
			msg[2*i] = partSize * i + shift;
			msg[2*i + 1] = partSize;
		} //clients with count_of_lines partSize
		for (int i = root+1; i < commSize; ++i) 
		{
			fprintf(stderr, "I'm root, send to %d start %d count %d\n", i, msg[2*i], msg[2*i+1]);//printing configs
			MPI_Send(msg + 2*i, 2, MPI_INT, i, Tag, MPI_COMM_WORLD);
			//sending tasks
		}
		//TRACE
		fun(engine, arr, msg[0], msg[1], nx);//the only using Trace Machine

		for (int i = root+1; i < commSize; ++i) 
		{
			MPI_Recv(arr + msg[2*i] * nx * 3, msg[2*i+1] * nx * 3, MPI_DOUBLE, i, Tag, MPI_COMM_WORLD, &status);
			//receiving results
		}

		//PPM
		std::cout << "P3\n" << nx << " " << ny << "\n255\n";//start filling ppm file with configs
		for(int j = ny-1; j >= 0; j--)//filling ppm file
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
		//MPI client
		MPI_Status status;
		int msg[2];//two ints to receive task
		MPI_Recv(msg, 2, MPI_INT, root, Tag, MPI_COMM_WORLD, &status);
		//usleep(1000 + 100*rank);
		//fprintf(stderr, "I'm %d, start is %d, count is %d\n", rank, msg[0], msg[1]);
		int start = msg[0];//start line
		int count = msg[1];//count of lines on picture
		double* arr = new double[count * nx * 3];//local line array to local part of picture
		fun(engine, arr, start, count, nx);//filling local part using Trace Machine
		MPI_Send(arr, count * nx * 3, MPI_DOUBLE, root, Tag, MPI_COMM_WORLD);//sending results
		delete[] arr;
	}

	MPI_Finalize();
}