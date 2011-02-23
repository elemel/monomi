#ifndef MONOMI_COLOR_HPP
#define MONOMI_COLOR_HPP

#include <iostream>

namespace monomi {
    enum ColorName {
        AQUA_COLOR,
        BLACK_COLOR,
        BLUE_COLOR,
        FUCHSIA_COLOR,
        GRAY_COLOR,
        GREEN_COLOR,
        LIME_COLOR,
        MAROON_COLOR,
        NAVY_COLOR,
        OLIVE_COLOR,
        PURPLE_COLOR,
        RED_COLOR,
        SILVER_COLOR,
        TEAL_COLOR,
        WHITE_COLOR,
        YELLOW_COLOR,

        COLOR_COUNT
    };

    std::ostream &operator<<(std::ostream &out, ColorName colorName);

    class Color3 {
    public:
        unsigned char red;
        unsigned char green;
        unsigned char blue;

        Color3();
        Color3(unsigned char red, unsigned char green, unsigned char blue);
        Color3(ColorName name);

        ColorName name() const;
    };

    inline Color3::Color3() :
        red(0), green(0), blue(0)
    { }

    inline Color3::Color3(unsigned char red, unsigned char green,
                          unsigned char blue) :
        red(red), green(green), blue(blue)
    { }

    std::ostream &operator<<(std::ostream &out, Color3 const &color);
}

#endif // MOMOMI_COLOR_HPP
