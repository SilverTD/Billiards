#include "Physics.h"

#include <math.h>

const double PI = std::atan(1) * 4;

auto Physics::getDistance(const Vector &vector, const Vector &vector2) -> double {
        return std::hypot(vector2.x - vector.x, vector2.y - vector.y);
}

auto Physics::getMouseAngle(const Vector &vector, const Vector &vector2) -> double {
        double opposite = vector2.y - vector.y;
        double adjacent = vector2.x - vector.x;

        return std::atan2(opposite, adjacent);
}

auto Physics::getStickAngle(const Vector &vector, const Vector &vector2) -> double {
        double opposite = vector2.y - vector.y;
        double hypotenuse = getDistance(vector, vector2);

        double degrees = (std::asin(opposite / hypotenuse) * 180) / PI + 180;

        if (vector.x > vector2.x) degrees = 180 - degrees;
        if (degrees < 0) degrees += 360;

        return degrees;
}
