#pragma once

class Vector {
        public:
                Vector(const double &x = 0, const double &y = 0):
                        x(x),
                        y(y)
                {};

                ~Vector() = default;

                Vector copy();
                Vector add(Vector vector);
                Vector subtract(Vector vector);
                Vector mult(const double &scalar);

                double dot(Vector vector);
                double length();

                double getX();
                double getY();

                void addTo(Vector vector);
                void setX(const double &x);
                void setY(const double &y);
        private:
                double
                        x,
                        y;
};
