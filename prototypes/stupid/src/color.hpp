#ifndef MONOMI_COLOR_HPP
#define MONOMI_COLOR_HPP

#include <iostream>

namespace monomi {
    enum ColorName {
        aquaColorName,
        blackColorName,
        blueColorName,
        fuchsiaColorName,
        grayColorName,
        greenColorName,
        limeColorName,
        maroonColorName,
        navyColorName,
        oliveColorName,
        purpleColorName,
        redColorName,
        silverColorName,
        tealColorName,
        whiteColorName,
        yellowColorName,

        colorNameCount
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
