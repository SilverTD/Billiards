#pragma once

#include <SDL2/SDL.h>

#include "Vector.h"

class Stick {
        public:
                Stick(SDL_Renderer *renderer, const Vector &position);
                ~Stick();

                /* Set */
                auto getPosition() -> Vector;
                auto getAngle() -> float;

                /* Get */
                void setAngle(const float &angle);
                void setPosition(const Vector &position);

                void update();
                void draw();

                void shoot();
                void setVelocity(const float &angle);
        private:
                SDL_Renderer *renderer = nullptr;
                SDL_Texture *texture = nullptr;

                SDL_Point
                        center = { -30, 15 };

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

                float
                        angle = 180;
};
