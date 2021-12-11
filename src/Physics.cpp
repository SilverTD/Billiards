#include "Physics.h"
#include "Globals.h"

#include <math.h>

/*
        Epic pythagorean theorem.
*/
auto Physics::getDistance(const Vector &vector, const Vector &vector2) -> float {
        return std::hypot(vector2.x - vector.x, vector2.y - vector.y);
}

/*
        Basic trigonometry math in grade 9.
*/
auto Physics::getMouseAngle(const Vector &vector, const Vector &vector2) -> float {
        const float opposite = vector2.y - vector.y;
        const float adjacent = vector2.x - vector.x;

        return std::atan2(opposite, adjacent);
}

auto Physics::getStickAngle(const Vector &vector, const Vector &vector2) -> float {
        const float opposite = vector2.y - vector.y;
        const float hypotenuse = getDistance(vector, vector2);

        float degrees = (std::asin(opposite / hypotenuse) * 180) / PI + 180;

        if (vector.x > vector2.x) degrees = 180 - degrees;
        if (degrees < 0) degrees += 360;

        return degrees;
}

auto Physics::checkCollision(const Ball *const objA, const Ball *const objB) -> bool {
        const Vector n = objA->getPosition() - objB->getPosition();

        const float dist = n.getMagnitude();

        return !(dist > BALL_DIAMETER);
}

/*
        Read more at: https://gamedevelopment.tutsplus.com/tutorials/when-worlds-collide-simulating-circle-circle-collisions--gamedev-769
*/
void Physics::resolveCollision(Ball *const objA, Ball *const objB) {
        if (!checkCollision(objA, objB)) return;

        const Vector n = objA->getPosition() - objB->getPosition();

        const float dist = n.getMagnitude();

        const Vector mtd = n * ((BALL_DIAMETER - dist) / dist);

        objA->setPosition(objA->getPosition() + mtd * 0.5f);
        objB->setPosition(objB->getPosition() - mtd * 0.5f);

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
