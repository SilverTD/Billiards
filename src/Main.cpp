#include <SDL2/SDL.h>

#include <SDL2/SDL_image.h>

#include <iostream>

#include "Globals.h"

#include "Ball.h"

#include "Stick.h"

#include "Physics.h"

using namespace Physics;

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;

int
        frameCount,
        timerFPS,
        lastFrame,
        fps,
        lastTime;

double
        power = 0.0;

bool
        running = true,
        isMouseDown = false,
        isMouseUp = false;

Ball
        *ball = nullptr,
        *ball2 = nullptr;

Stick *stick = nullptr;

void init() {
        ball = new Ball(renderer, Vector(400, 290), 0);
        ball2 = new Ball(renderer, Vector(700, 290), 1);
        stick = new Stick(renderer, ball->getPosition());
}

void update() {
        ball->update();
        ball2->update();
        stick->update();

        resolveCollision(ball, ball2);

        if (isMouseDown) {
                power += 0.8;

                int x, y;
                SDL_GetMouseState(&x, &y);

                double deg = getMouseAngle(ball->getPosition(), Vector(x, y));

                stick->increasePower(deg);
        }
        if (isMouseUp) {
                double angle = (stick->getAngle() * PI) / 180;

                stick->shoot();
                ball->shoot(power, angle);
                isMouseUp = false;
                power = 0.0;
        }

        if (!ball->isMoving() && !isMouseDown) stick->setPosition(ball->getPosition());
}

void input() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
                switch (event.type) {
                        case SDL_QUIT: running = false; break;
                        case SDL_MOUSEBUTTONDOWN:
                                if (ball->isMoving()) return;
                                isMouseDown = true;
                                isMouseUp = false;
                                break;
                        case SDL_MOUSEBUTTONUP:
                                if (ball->isMoving()) return;
                                isMouseDown = false;
                                isMouseUp = true;
                                break;
                        case SDL_MOUSEMOTION:
                                if (ball->isMoving()) return;

                                int x, y;
                                SDL_GetMouseState(&x, &y);

                                double degrees = getStickAngle(ball->getPosition(), Vector(x, y));

                                stick->setRotation(degrees);
                                break;
                }
        }
}

void tick() {
        lastFrame = SDL_GetTicks();
        if (lastFrame >= lastTime + 1000) {
                lastTime = lastFrame;
                fps = frameCount;
                frameCount = 0;
        }
}

void render() {
        SDL_SetRenderDrawColor(renderer, 10, 98, 50, 0.8);
        SDL_RenderClear(renderer);

        ++frameCount;
        timerFPS = SDL_GetTicks() - lastFrame;
        if (timerFPS < (1000 / 60)) {
                SDL_Delay((1000 / 60) - timerFPS);
        }

        ball->draw();
        ball2->draw();
        stick->draw();

        SDL_RenderPresent(renderer);
}

int main(int argc, char const *argv[]) {
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
                std::cout << "SDL_Init() failed" << '\n';
        if (SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer) < 0)
                std::cout << "SDL_CreateWindowAndRenderer() failed" << '\n';
        if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
                std::cout << "Failed to init SDL_Image" << '\n';
        SDL_SetWindowTitle(window, "Billiards");

        init();

        while (running) {
                tick();
                update();
                input();
                render();
        };

        delete stick;
        delete ball;
        delete ball2;

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();

        return 0;
}
