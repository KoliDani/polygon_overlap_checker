#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include <iostream>
#include <algorithm>
#include <list>

#define ZERO_TOL 1E-6
/*
 * BoundingBox class: contains the boundaries of the Polygon in double precision, 
 * also a numerical tolerance is applied to ensure the robustness of the code
 */
class BoundingBox {
public: 
	double xMin;
	double xMax;
	double yMin;
	double yMax;
    Polygon polygon;

    /*
     * Empty constructor
     */
    BoundingBox() {}

    /*
     * Constructor
     * Inputs: Polygon object
     */
    BoundingBox(Polygon& polygon) {
        this->polygon = polygon;

        if (polygon.isEmpty()) {  
            xMin = xMax = yMin = yMax = 0.0;
            return;
        }

        xMin = xMax = polygon.x[0];
        yMin = yMax = polygon.y[0];

        for (size_t i = 1; i < polygon.nrPoints(); i++) {
            xMin = std::min(xMin, polygon.x[i]);
            xMax = std::max(xMax, polygon.x[i]);
            yMin = std::min(yMin, polygon.y[i]);
            yMax = std::max(yMax, polygon.y[i]);
        }

        xMin -= ZERO_TOL;
        xMax += ZERO_TOL;
        yMin -= ZERO_TOL;
        yMax += ZERO_TOL;
    }

    /*
     * createBoundingBoxVector finds the possible intersection with bounding box based prefiltering
     * Input(s): A vector of Polygon objects
     */
    static std::vector<BoundingBox> createBoundingBoxVector(std::vector<Polygon> polygons) {
        std::vector<BoundingBox> boxes(polygons.size());

        for (size_t i = 0; i < polygons.size(); i++) {
            boxes[i] = BoundingBox(polygons[i]);
        }

        std::sort(boxes.begin(), boxes.end(), [](const BoundingBox& a, const BoundingBox& b) {
            return a.xMin < b.xMin; 
            });
    
        return boxes;
    }

    /*
     * createIntersectionMap finds the possible intersection with bounding box based prefiltering
     * Input(s): A vector of BoundingBox objects
     */
    static std::vector<std::vector<BoundingBox>> createIntersectionMap(std::vector<BoundingBox> boxes) {
        std::vector<std::list<BoundingBox>> intersectionMap(boxes.size());

        for (size_t i = 0; i < boxes.size() - 1; i++) {
            BoundingBox A = boxes[i];

            for (size_t j = i + 1; j < boxes.size(); j++) {
                BoundingBox B = boxes[j];

                if (A.xMax < B.xMin) {
                    // i+1 and so on will be further away
                    break; 
                }

                if (B.xMax < A.xMin || A.yMax < B.yMin || B.yMax < A.yMin) {
                    // Basic check for not intersection
                    continue;
                }

                intersectionMap[i].push_back(B);
                intersectionMap[j].push_back(A);
            }
        }

        std::vector<std::vector<BoundingBox>> outMap(intersectionMap.size());
        for (size_t i = 0; i < intersectionMap.size(); i++) {
            outMap[i] = std::vector<BoundingBox>(intersectionMap[i].begin(), intersectionMap[i].end());
        }

        return outMap;
    }

};

/*
 * Polygon::createIntersectionMap method implementation
 * Input(s): A vector of Polygon objects 
 */
std::vector<std::vector<Polygon>> Polygon::createIntersectionMap(std::vector<Polygon>& inputs) {
    std::vector<std::list<Polygon>> intersectionMap(inputs.size());
    std::vector<BoundingBox> box = BoundingBox::createBoundingBoxVector(inputs);
    std::vector<std::vector<BoundingBox>> boxIntersectionMap = BoundingBox::createIntersectionMap(box);

    for (size_t i = 0; i < boxIntersectionMap.size(); i++) {
        // Check if the polygon really intersects with the other polygon definition...
        Polygon A = box[i].polygon;
        intersectionMap[i].push_back(A);
        for (size_t j = 0; j < boxIntersectionMap[i].size(); j++) {
            Polygon B = boxIntersectionMap[i][j].polygon;
            if (A.isIntersect(B)) {
                intersectionMap[i].push_back(B);
            }
        }
    }

    std::vector<std::vector<Polygon>> outMap(intersectionMap.size());
    for (size_t i = 0; i < intersectionMap.size(); i++) {
        outMap[i] = std::vector<Polygon>(intersectionMap[i].begin(), intersectionMap[i].end());
    }

    return outMap;
}

#endif // BOUNDING_BOX_H