#include "Physics.h"

#include <math.h>

const double PI = std::atan(1) * 4;

double Physics::getDistance(Vector vector, Vector vector2) {
        return std::sqrt(std::pow(vector2.getX() - vector.getX(), 2) + std::pow(vector2.getY() - vector.getY(), 2));
}

double Physics::getMouseAngle(Vector vector, Vector vector2) {
        double opposite = vector2.getY() - vector.getY();
        double adjacent = vector2.getX() - vector.getX();

        return std::atan2(opposite, adjacent);
}

double Physics::getStickAngle(Vector vector, Vector vector2) {
        double opposite = vector2.getY() - vector.getY();
        double hypotenuse = std::hypot(vector2.getX() - vector.getX(), vector2.getY() - vector.getY());

        double degrees = (std::asin(opposite / hypotenuse) * 180) / PI + 180;

        if (vector.getX() > vector2.getX()) degrees = 180 - degrees;
        if (degrees < 0) degrees += 360;

        return degrees;
}
