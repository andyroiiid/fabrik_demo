//
// Created by andyroiiid on 4/21/2022.
//

#ifndef FABRIK_DEMO_BONES_H
#define FABRIK_DEMO_BONES_H

#include <vector>

#include "vector.h"

struct Bones {
    explicit Bones(const std::vector<Vec2> &points) noexcept;

    void fabrikSolve(const Vec2 &target, float tolerance = 0.001f, int maxIterations = 8);

    void draw() const;

private:
    float fabrikStep(const Vec2 &start, const Vec2 &target);

    void fabrikBackward(const Vec2 &target);

    void fabrikForward(const Vec2 &start);

    std::vector<Vec2> points;
    const std::vector<float> lengths;
    const int nBones;
};

#endif //FABRIK_DEMO_BONES_H
