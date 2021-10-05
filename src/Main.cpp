#include <SDL2/SDL.h>

#include <SDL2/SDL_image.h>

#include <iostream>

#include "Globals.h"

#include "Ball.h"

#include "Physics.h"

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;

int
        frameCount,
        timerFPS,
        lastFrame,
        fps,
        lastTime;

bool running = true;

Ball *ball = nullptr;

void init() {
        Vector position(100, 100);
        ball = new Ball(renderer, position, 0);
}

void update() {
        ball->update();
}

void input() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
                switch (event.type) {
                        case SDL_QUIT: running = false; break;
                        case SDL_MOUSEBUTTONDOWN:
                                int x, y;
                                SDL_GetMouseState(&x, &y);

                                Vector mousePos(x, y);

                                double rotation = Physics::getRotation(ball->getPos(), mousePos);
                                double power = Physics::getDistance(ball->getPos(), mousePos);

                                ball->shoot(power * 0.1, rotation);
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
        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(renderer);

        ++frameCount;
        timerFPS = SDL_GetTicks() - lastFrame;
        if (timerFPS < (1000 / 60)) {
                SDL_Delay((1000 / 60) - timerFPS);
        }

        ball->draw();

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

        delete ball;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();

        return 0;
}
