#ifndef MONOMI_CAMERA_HPP
#define MONOMI_CAMERA_HPP

#include "geometry.hpp"

namespace monomi {
    class Camera {
    public:
        Camera();

        Vector2 position;
        float scale;
    };
}

#endif // MONOMI_CAMERA_HPP
