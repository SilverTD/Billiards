#include "Physics.h"
#include "Globals.h"

#include <math.h>

auto Physics::getDistance(const Vector &vector, const Vector &vector2) -> double {
        return std::hypot(vector2.x - vector.x, vector2.y - vector.y);
}

auto Physics::getMouseAngle(const Vector &vector, const Vector &vector2) -> double {
        const double opposite = vector2.y - vector.y;
        const double adjacent = vector2.x - vector.x;

        return std::atan2(opposite, adjacent);
}

auto Physics::getStickAngle(const Vector &vector, const Vector &vector2) -> double {
        const double opposite = vector2.y - vector.y;
        const double hypotenuse = getDistance(vector, vector2);

        double degrees = (std::asin(opposite / hypotenuse) * 180) / PI + 180;

        if (vector.x > vector2.x) degrees = 180 - degrees;
        if (degrees < 0) degrees += 360;

        return degrees;
}

auto Physics::checkCollision(const Ball *const objA, const Ball *const objB) -> bool {
        const Vector n = objA->getPosition() - objB->getPosition();

        const float dist = n.getMagnitude();

        return !(dist > BALL_DIAMETER);
}

void Physics::resolveCollision(Ball *const objA, Ball *const objB) {
        if (!checkCollision(objA, objB)) return;

        const Vector n = objA->getPosition() - objB->getPosition();

        const float dist = n.getMagnitude();

        const Vector mtd = n * ((BALL_DIAMETER - dist) / dist);

        objA->setPosition(objA->getPosition() + mtd * (1 / 2));
        objB->setPosition(objB->getPosition() - mtd * (1 / 2));

        const Vector un = n * (1 / n.getMagnitude());
        const Vector ut = Vector(-un.y, un.x);

        const float v1n = un.dot(objA->getVelocity());
        const float v1t = ut.dot(objA->getVelocity());

        const float v2n = un.dot(objB->getVelocity());
        const float v2t = ut.dot(objB->getVelocity());

        const float v1nTag = v2n;
        const float v2nTag = v1n;

        const Vector v1nTag2 = un * v1nTag;
        const Vector v1tTag = ut * v1t;

        const Vector v2nTag2 = un * v2nTag;
        const Vector v2tTag = ut * v2t;

        objA->setVelocity(v1nTag2 + v1tTag);
        objB->setVelocity(v2nTag2 + v2tTag);

        objA->setMoving(true);
        objB->setMoving(true);
}
