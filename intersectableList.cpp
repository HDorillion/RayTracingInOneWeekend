#include "intersectableList.h"



void IntersectableList::clear() {
    objects.clear();
}
void IntersectableList::add(std::shared_ptr<Intersectable> object) {
    objects.push_back(object);
}

bool IntersectableList::intersects(const ray& r, double t_min, double t_max, intersection_record& rec) const {
    intersection_record temp_record;
    bool hit_something = false;

    auto closest_so_far = t_max;
    for (const auto& object : objects) {
        if (object->intersects(r, t_min, closest_so_far, temp_record)) {
            hit_something = true;
            closest_so_far = temp_record.t;
            rec = temp_record;
        }
    }

    return hit_something;
}