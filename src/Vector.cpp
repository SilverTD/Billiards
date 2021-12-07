#include "Vector.h"

#include <math.h>

/* Operators */
auto Vector::copy() const -> Vector {
        return Vector(x, y);
}

auto Vector::add(const Vector &vector) const -> Vector {
        return Vector(x + vector.x, y + vector.y);
}

auto Vector::subtract(const Vector &vector) const -> Vector {
        return Vector(x - vector.x, y - vector.y);
}

auto Vector::mult(const float &scalar) const -> Vector {
        return Vector(x * scalar, y * scalar);
}

auto Vector::addTo(const Vector &vector) -> Vector& {
        x += vector.x;
        y += vector.y;

        return *this;
}

auto Vector::operator+(const Vector &other) const -> Vector {
        return Vector(x + other.x, y + other.y);
}

auto Vector::operator+=(const Vector &other) -> Vector& {
        x += other.x;
        y += other.y;

        return *this;
}

auto Vector::operator-(const Vector &other) const -> Vector {
        return Vector(x - other.x, y - other.y);
}

/* Get */
auto Vector::dot(const Vector &vector) const -> float {
        return x * vector.x + y * vector.y;
}

auto Vector::getDirection() const -> float {
        return std::atan2(y, x);
}

auto Vector::getMagnitude() const -> float {
        return std::hypot(x, y);
}

auto Vector::angleBetween(const Vector &vector) const -> float {
        return std::atan2(x * vector.y - y * vector.x, x * vector.x + y * vector.y);
}

/* Set */
void Vector::setDirection(const float &direction) {
        auto magnitude = getMagnitude();
        x = std::cos(direction) * magnitude;
        y = std::sin(direction) * magnitude;
}

void Vector::setMagnitude(const float &magnitude) {
        auto direction = getDirection();
	x = std::cos(direction) * magnitude;
	y = std::sin(direction) * magnitude;
}

void Vector::setPosition(const Pos &position) {
        x = std::get<0>(position);
        y = std::get<1>(position);
}

void Vector::setPosition(const float &x, const float &y) {
        this->x = x;
        this->y = y;
}

/* Utilities */
auto Vector::getPosition() const -> Pos {
        return std::make_tuple(x, y);
}
