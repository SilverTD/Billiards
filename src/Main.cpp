#include <SDL2/SDL.h>

#include <SDL2/SDL_image.h>

#include <iostream>

#include "Globals.h"

#include "Ball.h"

#include "Stick.h"

#include "Physics.h"

const double PI = std::atan(1) * 4;

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;

int
        frameCount,
        timerFPS,
        lastFrame,
        fps,
        lastTime;

double power = 0.0;

bool
        running = true,
        isMouseDown = false,
        isMouseUp = false;

Ball *ball = nullptr;
Stick *stick = nullptr;

void init() {
        ball = new Ball(renderer, Vector(400, 290), 0);
        stick = new Stick(renderer, ball->getPos());
}

void update() {
        ball->update();
        stick->update();

        if (isMouseDown) {
                power += 0.8;

                int x, y;
                SDL_GetMouseState(&x, &y);

                double deg = Physics::getMouseAngle(ball->getPos(), Vector(x, y));

                stick->increasePower(deg);
        }
        if (isMouseUp) {
                double angle = (stick->getAngle() * PI) / 180;

                stick->shoot();
                ball->shoot(power, angle);
                isMouseUp = false;
                power = 0.0;
        }

        if (!ball->isMoving() && !isMouseDown) stick->setPos(ball->getPos());
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

                                double degrees = Physics::getStickAngle(ball->getPos(), Vector(x, y));

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
        SDL_SetWindowTitle(window, "Physics");

        init();

        while (running) {
                tick();
                update();
                input();
                render();
        };

        delete stick;
        delete ball;

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();

        return 0;
}
