#pragma once

#include <SDL2/SDL.h>

#include <array>

#include "Vector.h"

#include "Globals.h"

class Ball {
        public:
                Ball(SDL_Renderer *renderer, const Vector &position, const int &color);
                ~Ball();

                auto getPos() const -> Vector;
                auto isMoving() const -> bool;
                auto getVelocity() const -> Vector;

                void update(const double &delta = DELTA);
                void collideWithTable();
                void draw();
                void shoot(const double &power, const double &rotation);
                void setPos(const Vector &pos);
                void setMoving(bool&& moving);
                void setVelocity(const Vector &vector);

        private:
                static std::array<const char*, 2> colors;

                SDL_Renderer *renderer = nullptr;
                SDL_Texture *texture = nullptr;
                SDL_Rect rect;

                Vector
                        position,
                        velocity = Vector();

                int color;
                bool moving = false;
};
