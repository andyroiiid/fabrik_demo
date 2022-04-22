//
// Created by Andrew Huang on 4/15/2022.
//

#ifndef FABRIK_DEMO_RENDERER_H
#define FABRIK_DEMO_RENDERER_H

#include <SDL_render.h>
#include <SDL_events.h>

#include "vector.h"

constexpr SDL_Color BLACK{0x00, 0x00, 0x00, 0xFF};
constexpr SDL_Color RED{0xFF, 0x00, 0x00, 0xFF};
constexpr SDL_Color GREEN{0x00, 0xFF, 0x00, 0xFF};
constexpr SDL_Color BLUE{0x00, 0x00, 0xFF, 0xFF};
constexpr SDL_Color WHITE{0xFF, 0xFF, 0xFF, 0xFF};

typedef void (*EventCallback)(const SDL_Event &event);

typedef void (*FrameCallback)(float deltaTime);

void mainLoop(EventCallback onEvent, FrameCallback onFrame);

void setColor(const SDL_Color &color);

void drawPoint(const Vec2 &p, float size = 10.0f);

void drawLine(const Vec2 &p1, const Vec2 &p2);

#endif //FABRIK_DEMO_RENDERER_H
