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

        center = { -30, static_cast<int>(30 >> 1) };

        SDL_FreeSurface(surface);
}

Stick::~Stick() {
        SDL_DestroyTexture(texture);
}

Vector Stick::getPos() {
        return position;
}

double Stick::getAngle() {
        return rotation;
}

void Stick::update() {
        position.addTo(velocity);
}

void Stick::draw() {
        // x -> y -> w -> h

        dstrect = { static_cast<int>(position.getX() + 55), static_cast<int>(position.getY() + 10), 700, 20 };
        SDL_RenderCopyEx(renderer, texture, &srcrect, &dstrect, rotation, &center, SDL_FLIP_HORIZONTAL);
}

void Stick::setRotation(const double &rotation) {
        this->rotation = rotation;
}

void Stick::setPos(const double &x, const double &y) {
        position.setX(x);
        position.setY(y);

        origin = position;
}

void Stick::increasePower(const double &angle) {
        velocity = Vector(5 * cos(angle), 5 * sin(angle));
}

void Stick::shoot() {
        velocity = Vector();
        position = origin;
}
