// Source: https://raytracing.github.io/books/RayTracingInOneWeekend.html

#include "camera.h"
#include "color.h"
#include "intersectableList.h"
#include "lambertian.h"
#include "metal.h"
#include "ray.h"
#include "settings.h"
#include "sphere.h"
#include "utilities.h"

#include <iostream>

using namespace std;

color ray_color(const ray& r, const Intersectable& world, int depth) {
    if (depth <= 0) return color{ 0,0,0 };
    intersection_record record;
    if (world.intersects(r, 0.001, infinity, record)) {
        ray scattered_ray;
        color attenuation;
        if (record.mat_ptr->scatter(r, record, attenuation, scattered_ray))
            return attenuation * ray_color(scattered_ray, world, depth - 1);
        else
            return color(0, 0, 0);
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1., 1., 1.) + t * color(0.5, 0.7, 1.0);
}

int main() {
    std::cout
        << "P3\n"
        << settings::image_width << ' '
        << settings::image_height << "\n255\n";

    // Set world
    IntersectableList world({
        make_shared<Sphere>(
            point3(0, 0, -1), 0.5, make_shared<Lambertian>(color(0.7,0.3,0.3))),
        make_shared<Sphere>(
            point3(0, -100.5, -1), 100, make_shared<Lambertian>(color(0.8,0.9,0.0))),
        make_shared<Sphere>(
            point3(1, 0, -1), 0.5, make_shared<Metal>(color(0.8,0.6,0.2), 0.3)),
        make_shared<Sphere>(
            point3(-1, 0, -1), 0.5, make_shared<Metal>(color(0.8,0.8,0.8), 1.0)),
        });

    // Set camera
    Camera camera;

    for (int j = settings::image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < settings::image_width; ++i) {
            color pixel_color{ 0,0,0 };
            for (int s = 0; s < settings::samples_per_pixel; ++s) {
                auto u = (i + random_double()) / (settings::image_width - 1.);
                auto v = (j + random_double()) / (settings::image_height - 1.);
                ray r = camera.get_ray(u, v);
                pixel_color += ray_color(r, world, settings::max_depth);
            }
            write_color(std::cout, pixel_color, settings::samples_per_pixel);
        }
    }
    std::cerr << "Done.\n";
}
