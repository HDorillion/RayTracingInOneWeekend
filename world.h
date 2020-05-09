#pragma once

#include "dialectric.h"
#include "intersectableList.h"
#include "lambertian.h"
#include "metal.h"
#include "sphere.h"

#include <memory>

using std::make_shared;

IntersectableList get_world() {
    IntersectableList world({
    make_shared<Sphere>( // Central sphere
        point3(0, 0, -1), 0.5, make_shared<Lambertian>(color(0.1,0.2,0.5))),
    make_shared<Sphere>( // Ground
        point3(0, -100.5, -1), 100, make_shared<Lambertian>(color(0.8,0.9,0.0))),
    make_shared<Sphere>( // Reflective metallic sphere
        point3(1, 0, -1), 0.5, make_shared<Metal>(color(0.8,0.6,0.2), 0.0)),
    make_shared<Sphere>( // Fuzzy metallic sphere
        point3(-1, 0, -1), 0.5, make_shared<Metal>(color(0.8,0.8,0.8), 1.0)),
    make_shared<Sphere>( // Simple dialectric
        point3(-0.3, -0.5, -0.65), 0.15, make_shared<Dialectric>(1.5)),
    make_shared<Sphere>( // Simple dialectric
        point3(0.3, -0.3, -0.65), -0.15, make_shared<Dialectric>(1.5)),
    });
    return world;
}