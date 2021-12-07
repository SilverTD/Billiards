#pragma once

#include <SDL2/SDL.h>

#include "Vector.h"

class Stick {
        public:
                Stick(SDL_Renderer *renderer, const Vector &position);
                ~Stick();

                auto getPos() -> Vector;
                auto getAngle() -> double;

                void update();
                void draw();
                void setRotation(const double &rotation);
                void setPos(const Vector &position);
                void increasePower(const double &angle);
                void shoot();
        private:
                SDL_Renderer *renderer = nullptr;
                SDL_Texture *texture = nullptr;

                SDL_Point center;

                SDL_Rect
                        srcrect,
                        dstrect;

                Vector
                        position,
                        velocity = Vector(),
                        origin;

                int
                        textureWidth,
                        textureHeight;

                double
                        rotation = 0;
};
