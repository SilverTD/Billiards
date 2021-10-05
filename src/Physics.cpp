#include "Physics.h"

#include <math.h>

double Physics::getDistance(Vector vector, Vector vector2) {
        return sqrt(pow(vector2.getX() - vector.getX(), 2) + pow(vector2.getY() - vector.getY(), 2));
}

double Physics::getRotation(Vector vector, Vector vector2) {
        double opposite = vector2.getY() - vector.getY();
        double adjacent = vector2.getX() - vector.getY();

        return atan2(opposite, adjacent);
}
