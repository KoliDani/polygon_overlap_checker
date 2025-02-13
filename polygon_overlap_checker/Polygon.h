#ifndef POLYGON_H
#define POLYGON_H

#include <iostream>
#include <vector>
#include <list>
#include <string>

#define PI 3.14159265358979323846
/*
 * Polygon class: contains the coordinates in double precision and a defined name
 */
class Polygon {
public:
    std::vector<double> x;
    std::vector<double> y;
private:
    std::string name;
    
public:
    /*
     * Empty constructor
     */
    Polygon() {}

    /*
     * Constructor
     * Input(s): x and y coordinates of the polygon definition
     */
    Polygon(const std::vector<double>& x_coords, const std::vector<double>& y_coords) 
        : x(x_coords), y(y_coords) {

        if (x.size() != y.size()) {
            throw std::invalid_argument("Polygon x and y coordinates have different sizes.");
        }

        if (isEmpty()) {
            std::cerr << "Error: Polygon has no points." << std::endl;
        }
    }

    /*
     * Setter for the name property 
     * Input(s): name
     */
    void setName(std::string name) {
        this->name = name;
    }

    /*
     * Getter for the name property
     */
    std::string getName() {
        return this->name;
    }

     /*
      * Getter for the number of points in the polygon
      */
    size_t nrPoints() const {
        return x.size();
    }

    /*
     * Check if the polygon is empty or not
     */
    bool isEmpty() const {
        return x.size() == 0;
    }

    /*
     * Rotate the polygon around a defined point with an arbitrary angle (defined in degrees)
     * Input(s): cx (rotation center x), cy (rotation center y), angle
     */
    void rotate(double cx, double cy, double angleDeg) {
        double angleRad = angleDeg * PI / 180.0;

        for (size_t i = 0; i < x.size(); i++) {
            double dx = x[i] - cx;
            double dy = y[i] - cy;

            // Apply the rotation matrix
            x[i] = dx * cos(angleRad) - dy * sin(angleRad) + cx;
            y[i] = dx * sin(angleRad) + dy * cos(angleRad) + cy;
        }
    }

    /*
     * Create intersection map: only method definition, implementation is in BoundingBox.h
     */
    static std::vector<std::vector<Polygon>> createIntersectionMap(std::vector<Polygon>& inputs);

    /*
     * Check if an arbitrary point is inside the polygon or not
     * Input(s): px, py
     */
    bool isPointInside(double px, double py) {
        bool inside = false;
        for (size_t i = 0, j = x.size() - 1; i < x.size(); j = i++) {
            double xi = x[i], yi = y[i];
            double xj = x[j], yj = y[j];

            if ((yi > py) != (yj > py) && (px < (xj - xi) * (py - yi) / (yj - yi) + xi)) {
                inside = !inside;
            }
        }
        return inside;
    }

    /*
     * Check if a polygon intersects with the object polygon or not
     * Input(s): reference polygon
     */
    bool isIntersect(Polygon& B) {
        for (size_t i = 0; i < B.x.size(); i++) {
            if (isPointInside(B.x[i], B.y[i])) {
                return true;
            }
        }
        return false;
    }


};

#endif // POLYGON_H