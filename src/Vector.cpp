#include "Vector.h"

#include <math.h>

Vector Vector::copy() {
        return Vector(x, y);
}

Vector Vector::add(Vector vector) {
        return Vector(x + vector.getX(), y + vector.getY());
}

Vector Vector::subtract(Vector vector) {
        return Vector(x - vector.getX(), y - vector.getY());
}

Vector Vector::mult(const double &scalar) {
        return Vector(x * scalar, y * scalar);
}

double Vector::dot(Vector vector) {
        return x * vector.getX() + y * vector.getY();
}

double Vector::length() {
        return sqrt(pow(x, 2) + pow(y, 2));
}

double Vector::getX() {
        return x;
}

double Vector::getY() {
        return y;
}

void Vector::addTo(Vector vector) {
        x += vector.getX();
        y += vector.getY();
}

void Vector::setX(const double &x) {
        this->x = x;
}

void Vector::setY(const double &y) {
        this->y = y;
}
