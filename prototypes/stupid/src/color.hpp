#ifndef MONOMI_COLOR_HPP
#define MONOMI_COLOR_HPP

#include <iostream>

namespace monomi {
    enum ColorName {
        AQUA_COLOR_NAME,
        BLACK_COLOR_NAME,
        BLUE_COLOR_NAME,
        FUCHSIA_COLOR_NAME,
        GRAY_COLOR_NAME,
        GREEN_COLOR_NAME,
        LIME_COLOR_NAME,
        MAROON_COLOR_NAME,
        NAVY_COLOR_NAME,
        OLIVE_COLOR_NAME,
        PURPLE_COLOR_NAME,
        RED_COLOR_NAME,
        SILVER_COLOR_NAME,
        TEAL_COLOR_NAME,
        WHITE_COLOR_NAME,
        YELLOW_COLOR_NAME,

        COLOR_NAME_COUNT
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
