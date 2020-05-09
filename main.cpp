// Source: https://raytracing.github.io/books/RayTracingInOneWeekend.html

#include "camera.h"
#include "color.h"
#include "intersectableList.h"
#include "settings.h"
#include "sphere.h"
#include "utilities.h"

#include <iostream>

using namespace std;

color ray_color(const ray& r, const Intersectable& world, int depth) {
    if (depth <= 0) return color{ 0,0,0 };
    hit_record record;
    if (world.intersects(r, 0.001, infinity, record)) {
        point3 target = record.p + record.normal + random_unit_vector();
        return 0.5 * ray_color(ray(record.p, target - record.p), world, depth - 1);
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
        make_shared<sphere>(point3{ 0, 0, -1 }, 0.5),
        make_shared<sphere>(point3{0, -100.5, -1}, 100)
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
