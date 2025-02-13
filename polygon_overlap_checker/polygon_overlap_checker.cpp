#include <iostream>
#include "Polygon.h"
#include "BoundingBox.h"

/*
 * printIntersectionMap: Print out the found intersections with the help of the polygons' name property
 * Input(s): intersectionMap
 */
void printIntersectionMap(std::vector<std::vector<Polygon>> intersectionMap) {
    for (size_t i = 0; i < intersectionMap.size(); i++) {
        std::cout << intersectionMap[i][0].getName();

        if (intersectionMap[i].size() < 2) {
            // No intersect found
            std::cout << " has no intersection with other polygons." << std::endl;
            continue;
        }

        std::cout << " intersects with: ";

        for (size_t j = 1; j < intersectionMap[i].size(); j++) {
            std::cout << intersectionMap[i][j].getName() + ", ";
        }
        std::cout << "\b\b \b\b";
        std::cout << std::endl;
    }
}

int main() {

    /*
     * Create the following test case: 
     *
     *    ______________          ____________
     *   |              |        |            |
     *   |      A       |        |            |
     *   |       _______|________|__    C     |
     *   |      |       |        |  |         |
     *   |______|_______| B   ___|__|___      |
     *          |            |   |__|___|_____|
     *          |____________|______|   |
     *                       |          |
     *                       |    D     |
     *                       |__________|
     *
     *  This means, that the code should return the following intersections:
     *      -A: B
     *      -B: A,C,D
     *      -C: B,D
     *      -D: B,C
     * 
     */

    int NR_POLY = 4;

    std::vector<double> aX = { 0.0, 10.0, 10.0, 0.0 };
    std::vector<double> aY = { 0.0, 0.0, 10.0, 10.0 };

    std::vector<double> bX = { 5.0, 20.0, 20.0, 5.0 };
    std::vector<double> bY = { 5.0, 5.0, -5.0, -5.0 };

    std::vector<double> cX = { 18.0, 25.0, 25.0, 18.0 };
    std::vector<double> cY = { 0.0, 0.0, -10.0, -10.0 };

    std::vector<double> dX = { 19.0, 30.0, 30.0, 19.0 };
    std::vector<double> dY = { -2.0, -2.0, 10.0, 10.0 };

    std::vector<Polygon> polys(NR_POLY);
    int i = 0;
    polys[i++] = Polygon(aX, aY);
    polys[i++] = Polygon(bX, bY);
    polys[i++] = Polygon(cX, cY);
    polys[i++] = Polygon(dX, dY);

    i = 0;
    polys[i++].setName("A");
    polys[i++].setName("B");
    polys[i++].setName("C");
    polys[i++].setName("D");

    i = 0;
    polys[i++].rotate(0, 0, 25);
    polys[i++].rotate(0, 0, 25);
    polys[i++].rotate(0, 0, 25);
    polys[i++].rotate(0, 0, 25);

    printIntersectionMap(Polygon::createIntersectionMap(polys));
}