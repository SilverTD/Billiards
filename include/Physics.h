#include "Vector.h"
#include "Ball.h"

namespace Physics {
        auto getDistance(const Vector &vector, const Vector &vector2) -> float;
        auto getMouseAngle(const Vector &vector, const Vector &vector2) -> float;
        auto getStickAngle(const Vector &vector, const Vector &vector2) -> float;
        auto checkCollision(const Ball *const objA, const Ball *const objB) -> bool;

        void resolveCollision(Ball *const objA, Ball *const objB);
}
