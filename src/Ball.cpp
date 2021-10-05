#include <SDL2/SDL_image.h>

#include <math.h>

#include "Ball.h"

std::array<const char*, 2> Ball::colors = {
        "./assets/ball.png", "./assets/ball2.png"
};

Ball::Ball(SDL_Renderer *renderer, const Vector &position, const int &color):
renderer(renderer), position(position), color(color) {
        SDL_Surface *surface = IMG_Load(colors[color]);
	texture = SDL_CreateTextureFromSurface(renderer, surface);

        SDL_FreeSurface(surface);
};

Ball::~Ball() {
        SDL_DestroyTexture(texture);
}

void Ball::update(const double &delta) {
        collideWithTable();

        velocity.mult(delta);
        position.addTo(velocity);

        // Friction
        velocity = velocity.mult(0.984);

        if (velocity.length() < 0.1) {
                velocity = Vector();
                isMoving = false;
        }
}

void Ball::collideWithTable() {
        if (!isMoving) return;

        if (position.getY() <= 0) {
                position.setY(0);
                velocity = Vector(velocity.getX(), -velocity.getY());
        }
        else if (position.getY() >= SCREEN_HEIGHT - BALL_DIAMETER) {
                position.setY(SCREEN_HEIGHT - BALL_DIAMETER);
                velocity = Vector(velocity.getX(), -velocity.getY());
        }
        if (position.getX() <= 0) {
                position.setX(0);
                velocity = Vector(-velocity.getX(), velocity.getY());
        }
        else if (position.getX() >= SCREEN_WIDTH - BALL_DIAMETER) {
                position.setX(SCREEN_WIDTH - BALL_DIAMETER);
                velocity = Vector(-velocity.getX(), velocity.getY());
        }
}

void Ball::draw() {
        // x -> y -> w -> h

        rect = { static_cast<int>(position.getX()), static_cast<int>(position.getY()), 50, 50 };
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

void Ball::shoot(const double &power, const double &rotation) {
        velocity = Vector(power * cos(rotation), power * sin(rotation));
        isMoving = true;
}

Vector Ball::getPos() const {
        return position;
}
