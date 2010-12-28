#ifndef MONOMI_GRID_HPP
#define MONOMI_GRID_HPP

#include "geometry.hpp"

#include <boost/function.hpp>
#include <boost/unordered_map.hpp>

namespace monomi {
    class Grid {
    public:
        typedef boost::function<void (int)> QueryCallback;

        explicit Grid(Box2 const &boundingBox, float cellSize = 1.0f);

        Box2 const &boundingBox() const;
        float cellSize() const;

        void insert(int key, Box2 const &boundingBox);
        void erase(int key);
        void query(Box2 const &boundingBox, QueryCallback const &callback);

    private:
        typedef boost::unordered_map<int, Box2> BoundingBoxMap;

        Box2 boundingBox_;
        float cellSize_;
        BoundingBoxMap boundingBoxes_;
    };
}

#endif // MONOMI_GRID_HPP
