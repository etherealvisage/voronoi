#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <cstring>

#include "voronoi.hpp"

using namespace voronoi;

int main() {
    for(int i = 0; i < 1; i ++) {
    std::vector<point> original;
    std::vector<double> weights;

    for(int i = 0; i < 400; i ++) {
        original.push_back(point(rand() % 1000, rand() % 1000));
        weights.push_back(1);
    }
    /*original.push_back(point(0, 0)); weights.push_back(1.0);
    original.push_back(point(1, 0)); weights.push_back(1.0);
    original.push_back(point(0, 1)); weights.push_back(1.0);
    original.push_back(point(.9, .9)); weights.push_back(1.0);*/
    //original.push_back(point(0, 0)); weights.push_back(1.0);
    //original.push_back(point(-1, 0)); weights.push_back(1.0);
    //original.push_back(point(1, 1)); weights.push_back(1.0);
    //original.push_back(point(1, -1)); weights.push_back(1.0);

    auto results = compute_voronoi(original, weights);
    }

    /*std::ofstream p("points");
    for(unsigned i = 0; i < original.size(); i ++) {
        p << original[i].x() << " " << original[i].y() << std::endl;
    }

    for(unsigned i = 0; i < results.size(); i ++) {
        char name[100];
        sprintf(name, "poly-%u", i);
        std::ofstream f(name);
        auto &poly = results[i];
        for(unsigned j = 0; j < poly.size(); j ++) {
            std::cout << " (" << poly[j].x() << ", " << poly[j].y() << ")";
            f << "" << poly[j].x() << " " << poly[j].y() << "" << std::endl;
        }
        f << "" << poly[0].x() << " " << poly[0].y() << "" << std::endl;
        f << std::endl;
        std::cout << std::endl;
    }*/

    return 0;
}
