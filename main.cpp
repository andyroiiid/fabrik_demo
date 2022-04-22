#include <memory>
#include <random>
#include <SDL.h>

#include "renderer.h"
#include "bones.h"

Vec2 mousePos;

std::unique_ptr<Bones> bones;
Vec2 target;

static float randomFloat() {
    static std::mt19937 generator(std::random_device{}());
    static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
    return distribution(generator);
}

void init() {
    Vec2 p{400.0f, 300.0f};
    std::vector<Vec2> points;
    for (int i = 0; i < 8; i++) {
        points.push_back(p);
        p.x += randomFloat() * 90.0f + 10.0f;
    }
    bones = std::make_unique<Bones>(points);
}

static Vec2 linearInterpolation(const Vec2 &a, const Vec2 &b, float t) {
    return a * (1 - t) + b * t;
}

void eventCallback(const SDL_Event &event) {
    if (event.type == SDL_MOUSEMOTION) {
        const auto &motion = event.motion;
        mousePos.x = static_cast<float>(motion.x);
        mousePos.y = static_cast<float>(motion.y);
    }
}

void frameCallback(float deltaTime) {
    target = linearInterpolation(target, mousePos, 10.0f * deltaTime);
    bones->fabrikSolve(target);
    bones->draw();
}

int main(int, char *[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    init();
    mainLoop(eventCallback, frameCallback);
    SDL_Quit();
    return 0;
}
