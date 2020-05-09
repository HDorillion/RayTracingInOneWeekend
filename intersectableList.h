#pragma once

#include "intersectable.h" // base class

#include <memory>
#include <vector>

// Represents a collection of Intersectable objects
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

    // Clears the object collection
    void clear();
    // Adds an object to the collection
    void add(std::shared_ptr<Intersectable> object);
    // Returns true and modifies rec if an object intersects r with the given range
    virtual bool intersects(const ray& r, double t_min, double t_max, intersection_record& rec) const;
};
