#ifndef POINT2D_H
#define POINT2D_H

#include <string>

struct Point2D {
public:
    Point2D(int x, int y): x(x), y(y){};
	Point2D() = default;

    int x, y;
    bool operator== (const Point2D& rhs) const;
    bool operator!= (const Point2D& rhs) const;
    Point2D& operator= (const Point2D& rhs);

	std::string toString() const { return "(" + std::to_string(x) + " , " + std::to_string(y) + ")"; };
};

#endif //POINT2D_H
