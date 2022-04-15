#include <SDL.h>

#include "renderer.h"

struct Bones {
    Bones(const Vec2 &p1, const Vec2 &p2, const Vec2 &p3, const Vec2 &p4) noexcept
            : p1(p1),
              p2(p2),
              p3(p3),
              p4(p3),
              l1((p2 - p1).length()),
              l2((p3 - p2).length()),
              l3((p4 - p3).length()) {}

    Vec2 p1;
    Vec2 p2;
    Vec2 p3;
    Vec2 p4;

    const float l1;
    const float l2;
    const float l3;

    void fabrik(const Vec2 &target, float tolerance = 0.001f, int maxIterations = 8) {
        const Vec2 start = p1;
        for (int i = 0; i < maxIterations; i++) {
            if (fabrikStep(start, target) <= tolerance)
                break;
        }
    }

    void draw() const {
        setColor(WHITE);
        drawPoint(p1);
        drawPoint(p2);
        drawPoint(p3);
        drawPoint(p4);
        drawLine(p1, p2);
        drawLine(p2, p3);
        drawLine(p3, p4);
    }

private:
    static Vec2 solveBone(const Vec2 &from, const Vec2 &to, float length) {
        return from + (to - from).normalize() * length;
    }

    void fabrikBackward(const Vec2 &target) {
        p4 = target;
        p3 = solveBone(p4, p3, l3);
        p2 = solveBone(p3, p2, l2);
        p1 = solveBone(p2, p1, l1);
    }

    void fabrikForward(const Vec2 &start) {
        p1 = start;
        p2 = solveBone(p1, p2, l1);
        p3 = solveBone(p2, p3, l2);
        p4 = solveBone(p3, p4, l3);
    }

    float fabrikStep(const Vec2 &start, const Vec2 &target) {
        fabrikBackward(target);
        fabrikForward(start);
        return (p4 - target).length();
    }
};

Bones bones(
        {100.0f, 100.0f},
        {200.0f, 200.0f},
        {400.0f, 200.0f},
        {500.0f, 100.0f}
);

Vec2 target{300.0f, 200.0f};

void eventCallback(const SDL_Event &event) {
    if (event.type == SDL_MOUSEMOTION) {
        const auto &motion = event.motion;
        target.x = static_cast<float>(motion.x);
        target.y = static_cast<float>(motion.y);
    }
}

void frameCallback() {
    bones.fabrik(target);
    bones.draw();
}

int main(int, char *[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    mainLoop(eventCallback, frameCallback);
    SDL_Quit();
    return 0;
}
