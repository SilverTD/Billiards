#include "Vector.h"

namespace Physics {
        auto getDistance(const Vector &vector, const Vector &vector2) -> double;
        auto getMouseAngle(const Vector &vector, const Vector &vector2) -> double;
        auto getStickAngle(const Vector &vector, const Vector &vector2) -> double;
}
