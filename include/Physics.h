#include "Vector.h"
#include "Ball.h"

namespace Physics {
        auto getDistance(const Vector &vector, const Vector &vector2) -> double;
        auto getMouseAngle(const Vector &vector, const Vector &vector2) -> double;
        auto getStickAngle(const Vector &vector, const Vector &vector2) -> double;
        auto checkCollision(const Ball *const objA, const Ball *const objB) -> bool;

        void resolveCollision(Ball *const objA, Ball *const objB);
}
