# Polygon Overlap Checker

## Overview
Polygon Overlap Checker is a C++ dummy project designed to efficiently detect overlapping polygons. It uses a bounding box strategy to quickly filter out non-overlapping polygons before performing precise intersection (point in polygon) checks.

## Features
- **Efficient Bounding Box Filtering**: Uses bounding boxes to speed up intersection detection.
- **Custom Polygon Class**: Stores polygon coordinates and provides utility methods.
- **Intersection Detection**: Groups polygons based on overlaps.
- **Header-Only Implementation**: No separate `.cpp` files required.

## Test
The following test case is implemented in polygon_overlap_checker.cpp <br />
![image](https://github.com/user-attachments/assets/59921c8f-aea0-4bc4-98bf-135fbf91e594)

## Installation
To use this project, simply clone the repository and compile the program using a C++ compiler that supports C++11 or later.

```sh
git clone https://github.com/KoliDani/polygon_overlap_checker.git
cd polygon_overlap_checker
```

## Usage
### 1. Include Headers
Ensure you include the necessary header files in your C++ project:
```cpp
#include "Polygon.h"
#include "BoundingBox.h"
```

### 2. Creating a Polygon
```cpp
std::vector<double> x = {1.0, 2.0, 3.0};
std::vector<double> y = {4.0, 5.0, 6.0};
Polygon poly(x, y);
```

### 3. Checking for Intersections
```cpp
std::vector<Polygon> polygons = {poly1, poly2, poly3};
auto intersectionGroups = Polygon.getIntersectionMap(polygons);
```

## License
This project is licensed under the MIT License. See `LICENSE` for details.

## Contact
For any questions or suggestions, feel free to reach out:
- **GitHub**: [KoliDani](https://github.com/KoliDani)
