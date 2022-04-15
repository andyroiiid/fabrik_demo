//
// Created by Andrew Huang on 4/15/2022.
//

#include "renderer.h"

static SDL_Window *window = nullptr;
static SDL_Renderer *renderer = nullptr;

void mainLoop(EventCallback onEvent, FrameCallback onFrame) {
    window = SDL_CreateWindow("FABRIK demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);

    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                break;
            }
            onEvent(event);
        }

        setColor(BLACK);
        SDL_RenderClear(renderer);

        onFrame();

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void setColor(const SDL_Color &color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

void drawPoint(const Vec2 &p, float size) {
    const SDL_FRect rect{
            p.x - size * 0.5f,
            p.y - size * 0.5f,
            size,
            size
    };
    SDL_RenderDrawRectF(renderer, &rect);
}

void drawLine(const Vec2 &p1, const Vec2 &p2) {
    SDL_RenderDrawLineF(renderer, p1.x, p1.y, p2.x, p2.y);
}
