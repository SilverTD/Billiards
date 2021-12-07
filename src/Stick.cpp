#include <SDL2/SDL_image.h>

#include <math.h>

#include "Stick.h"

Stick::Stick(SDL_Renderer *renderer, const Vector &position):
renderer(renderer), position(position), origin(position) {
        SDL_Surface *surface = IMG_Load("./assets/stick.png");
        texture = SDL_CreateTextureFromSurface(renderer, surface);

        SDL_QueryTexture(texture, nullptr, nullptr, &textureWidth, &textureHeight);

        srcrect.x = srcrect.y = 0;
        srcrect.w = textureWidth;
        srcrect.h = textureHeight;

        center = { -30, 15 };

        SDL_FreeSurface(surface);
}

Stick::~Stick() {
        SDL_DestroyTexture(texture);
}

auto Stick::getPos() -> Vector {
        return position;
}

auto Stick::getAngle() -> double {
        return rotation;
}

void Stick::update() {
        position += velocity;
}

void Stick::draw() {
        // x -> y -> w -> h

        dstrect = { static_cast<int>(position.x + 55), static_cast<int>(position.y + 10), 700, 20 };
        SDL_RenderCopyEx(renderer, texture, &srcrect, &dstrect, rotation, &center, SDL_FLIP_HORIZONTAL);
}

void Stick::setRotation(const double &rotation) {
        this->rotation = rotation;
}

void Stick::setPos(const Vector &vector) {
        position.setPosition({ vector.x, vector.y });

        origin = position;
}

void Stick::increasePower(const double &angle) {
        velocity = Vector(-5 * std::cos(angle), -5 * std::sin(angle));
}

void Stick::shoot() {
        velocity = Vector();
        position = origin;
}
