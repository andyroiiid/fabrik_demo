//
// Created by andyroiiid on 4/21/2022.
//

#include "bones.h"

#include "renderer.h"

static std::vector<float> calcBoneLengths(const std::vector<Vec2> &points) {
    std::vector<float> lengths;
    const int nBones = static_cast<int>(points.size() - 1);
    for (int i = 0; i < nBones; i++) {
        lengths.push_back((points[i + 1] - points[i]).length());
    }
    return lengths;
}

Bones::Bones(const std::vector<Vec2> &points) noexcept
        : points(points),
          lengths(calcBoneLengths(points)),
          nBones(static_cast<int>(lengths.size())) {}

void Bones::fabrikSolve(const Vec2 &target, float tolerance, int maxIterations) {
    const Vec2 start = points.front();
    for (int i = 0; i < maxIterations; i++) {
        if (fabrikStep(start, target) <= tolerance)
            break;
    }
}

float Bones::fabrikStep(const Vec2 &start, const Vec2 &target) {
    fabrikBackward(target);
    fabrikForward(start);
    return (points.back() - target).length();
}

static Vec2 solveBone(const Vec2 &from, const Vec2 &to, float length) {
    return from + (to - from).normalize() * length;
}

void Bones::fabrikBackward(const Vec2 &target) {
    points[nBones] = target;
    for (int i = nBones - 1; i >= 0; i--) {
        points[i] = solveBone(points[i + 1], points[i], lengths[i]);
    }
}

void Bones::fabrikForward(const Vec2 &start) {
    points[0] = start;
    for (int i = 1; i <= nBones; i++) {
        points[i] = solveBone(points[i - 1], points[i], lengths[i - 1]);
    }
}

void Bones::draw() const {
    setColor(WHITE);
    for (const auto &point: points) {
        drawPoint(point);
    }
    for (int i = 0; i < nBones; i++) {
        drawLine(points[i], points[i + 1]);
    }
}
