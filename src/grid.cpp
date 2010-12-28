#include "grid.hpp"

namespace monomi {
    Grid::Grid(Box2 const &boundingBox, float cellSize) :
        boundingBox_(boundingBox),
        cellSize_(cellSize)
    { }

    Box2 const &Grid::boundingBox() const
    {
        return boundingBox_;
    }

    float Grid::cellSize() const
    {
        return cellSize_;
    }

    void Grid::insert(int key, Box2 const &boundingBox)
    {
        boundingBoxes_.insert(std::make_pair(key, boundingBox));
    }

    void Grid::erase(int key)
    {
        boundingBoxes_.erase(key);
    }

    void Grid::query(Box2 const &boundingBox, QueryCallback const &callback)
    {
        for (BoundingBoxMap::iterator i = boundingBoxes_.begin();
             i != boundingBoxes_.end(); ++i)
        {
            if (intersects(i->second, boundingBox)) {
                callback(i->first);
            }
        }
    }
}
