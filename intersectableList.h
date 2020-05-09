#pragma once

#include "intersectable.h" // base class

#include <memory>
#include <vector>

class IntersectableList :
    public Intersectable
{
    std::vector<std::shared_ptr<Intersectable>> objects;

public:
    IntersectableList() = delete;
    IntersectableList(std::shared_ptr<Intersectable> object) { add(object); }
    IntersectableList(std::vector<std::shared_ptr<Intersectable>> objs) {
        for (const auto& obj : objs) {
            add(obj);
        }
    }

    void clear();
    void add(std::shared_ptr<Intersectable> object);

    virtual bool intersects(const ray& r, double t_min, double t_max, hit_record& rec) const;
};
