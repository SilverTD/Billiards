#pragma once

#include <SDL2/SDL.h>

#include <array>

#include "Vector.h"

class Ball {
        public:
                Ball(SDL_Renderer *renderer, const Vector &position, const int &color);
                ~Ball();

                /* Set */
                auto getPosition() const -> Vector;
                auto isMoving() const -> bool;
                auto getVelocity() const -> Vector;

                /* Get */
                void setPosition(const Vector &pos);
                void setMoving(bool&& moving);
                void setVelocity(const Vector &vector);

                void update();
                void collideWithTable();
                void draw();
                void shoot(const double &power, const double &angle);
        private:
                static std::array<const char*, 2> colors;

                SDL_Renderer *renderer = nullptr;
                SDL_Texture *texture = nullptr;

                SDL_Rect
                        rect;

                Vector
                        position,
                        velocity;

                int
                        color;

                bool
                        moving = false;
};
