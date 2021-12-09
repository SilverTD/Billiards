#include <SDL2/SDL.h>

#include <SDL2/SDL_image.h>

#include <iostream>

#include <array>

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

Ball *ball = nullptr;

Stick *stick = nullptr;

std::array<Ball*, 16> balls { { nullptr } };

inline auto getMousePosition() -> Vector {
        int x, y;
        SDL_GetMouseState(&x, &y);

        return Vector(x, y);
}

void freeBalls() {
        for (unsigned int i = 0; i < balls.size(); ++i)
                delete balls[i];
}

void init() {
        /* Init Balls. */
        ball = balls[0] = new Ball(renderer, Vector(413, 413 - 100), 0);
        balls[1] = new Ball(renderer, Vector(1090, 413 - 100), 3);
        balls[2] = new Ball(renderer, Vector(1056, 433 - 100), 1);
        balls[3] = new Ball(renderer, Vector(1090, 374 - 100), 2);
        balls[4] = new Ball(renderer, Vector(1126, 393 - 100), 1);
        balls[5] = new Ball(renderer, Vector(1126, 472 - 100), 2);
        balls[6] = new Ball(renderer, Vector(1162, 335 - 100), 1);
        balls[7] = new Ball(renderer, Vector(1162, 374 - 100), 2);
        balls[8] = new Ball(renderer, Vector(1162, 452 - 100), 1);
        balls[9] = new Ball(renderer, Vector(1022, 413 - 100), 2);
        balls[10] = new Ball(renderer, Vector(1056, 393 - 100), 1);
        balls[11] = new Ball(renderer, Vector(1090, 452 - 100), 2);
        balls[12] = new Ball(renderer, Vector(1126, 354 - 100), 1);
        balls[13] = new Ball(renderer, Vector(1126, 433 - 100), 2);
        balls[14] = new Ball(renderer, Vector(1162, 413 - 100), 1);
        balls[15] = new Ball(renderer, Vector(1162, 491 - 100), 2);

        /* Init Stick. */
        stick = new Stick(renderer, ball->getPosition());
}

void update() {
        ball->update();
        stick->update();

        for (unsigned int i = 0; i < balls.size(); ++i) {
                balls[i]->update();
                for (unsigned int j = i + 1; j < balls.size(); ++j) {
                        resolveCollision(balls[i], balls[j]);
                }
        }

        // resolveCollision(ball, ball2);
        if (isMouseDown) {
                power += 0.8;

                auto degrees = getMouseAngle(
                        ball->getPosition(),
                        getMousePosition()
                );

                stick->inreasePosition(degrees);
        }

        if (isMouseUp) {
                auto angle = (stick->getAngle() * PI) / 180;

                stick->shoot();
                ball->shoot(power, angle);
                isMouseUp = false;
                power = 0.0;
        }

        if (!ball->isMoving() && !isMouseDown)
                stick->setPosition(ball->getPosition());
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

                                auto degrees = getStickAngle(
                                        ball->getPosition(),
                                        getMousePosition()
                                );

                                stick->setAngle(degrees);
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
        for (auto &current_ball : balls) {
                current_ball->draw();
        }
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

        freeBalls();
        delete stick;

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();

        return 0;
}
