#pragma once

#include <SDL2/SDL.h>

#include "Vector.h"

class Stick {
        public:
                Stick(SDL_Renderer *renderer, const Vector &position);
                ~Stick();

                /* Set */
                auto getPosition() -> Vector;
                auto getAngle() -> double;

                /* Get */
                void setRotation(const double &rotation);
                void setPosition(const Vector &position);

                void update();
                void draw();
                void increasePower(const double &angle);
                void shoot();
        private:
                SDL_Renderer *renderer = nullptr;
                SDL_Texture *texture = nullptr;

                SDL_Point
                        center = { -30, 15 };;

                SDL_Rect
                        srcrect,
                        dstrect;

                Vector
                        position,
                        velocity,
                        origin;

                int
                        textureWidth,
                        textureHeight;

                double
                        rotation = 180;
};
