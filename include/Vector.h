#pragma once

#include <tuple>

class Vector {
        public:
                Vector(const float &x = 0.0f, const float &y = 0.0f) :
                        x(x),
                        y(y)
                {};

                Vector(const Vector &vector) :
                        x(vector.x),
                        y(vector.y)
                {};

                ~Vector() = default;

                /* Operators */
                auto copy() const -> Vector;
                auto add(const Vector &vector) const -> Vector;
                auto subtract(const Vector &vector) const -> Vector;
                auto mult(const float &scalar) const -> Vector;
                auto operator+(const Vector &other) const -> Vector;
                auto operator-(const Vector &other) const -> Vector;
                void addTo(const Vector &vector);

                /* Get */
                auto dot(const Vector &vector) const -> float;
                auto getDirection() const -> float;
                auto getMagnitude() const -> float;
                auto angleBetween(const Vector &vector) const -> float;

                /* Set */
                void setDirection(const float &direction);
                void setMagnitude(const float &magnitude);
                void setPosition(const std::tuple<float, float> &position);
                void setPosition(const float &x, const float &y);

                /* Utilities */
                auto getPosition() const -> std::tuple<float, float>;

                float
                        x,
                        y;
};
