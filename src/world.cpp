#include <porto/world.h>
#include <iostream>
#include <fstream>
/*
porto::World::World(int argc, char *argv[]) : mpi_unit{argc, argv}
{
    if (argc >= 1) {
        conf_file.open(argv[1]);
        if (conf_file.is_open())
            return;
    }
    for (;;) {
        std::cout << "\nType path to configuration file or press Ctrl + D\n>>> ";
        if (std::cin.eof()) return;
        std::string f;
        std::cin >> f;
        conf_file.open(f.c_str());
        if (conf_file.is_open());
            return;
    }
}

int porto::World::init()
{
    return 0;
}
*/