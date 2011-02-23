#include "color.hpp"

namespace monomi {
    namespace {
        unsigned char namedColors[] = {
            0x00, 0xff, 0xff, // aqua
            0x00, 0x00, 0x00, // black
            0x00, 0x00, 0xff, // blue
            0xff, 0x00, 0xff, // fuchsia
            0x80, 0x80, 0x80, // gray
            0x00, 0x80, 0x00, // green
            0x00, 0xff, 0x00, // lime
            0x80, 0x00, 0x00, // maroon
            0x00, 0x00, 0x80, // navy
            0x80, 0x80, 0x00, // olive
            0x80, 0x00, 0x80, // purple
            0xff, 0x00, 0x00, // red
            0xc0, 0xc0, 0xc0, // silver
            0x00, 0x80, 0x80, // teal
            0xff, 0xff, 0xff, // white
            0xff, 0xff, 0x00 // yellow
        };

        inline int square(int i)
        {
            return i * i;
        }

        inline int squaredDistance(Color3 const &c1, Color3 const &c2)
        {
            return (square(int(c2.red) - int(c1.red)) +
                    square(int(c2.green) - int(c1.green)) +
                    square(int(c2.blue) - int(c1.blue)));
        }
    }

    std::ostream &operator<<(std::ostream &out, ColorName colorName)
    {
        switch (colorName) {
        case AQUA_COLOR:
            return out << "aqua";

        case BLACK_COLOR:
            return out << "black";

        case BLUE_COLOR:
            return out << "blue";

        case FUCHSIA_COLOR:
            return out << "fuchsia";

        case GRAY_COLOR:
            return out << "gray";

        case GREEN_COLOR:
            return out << "green";

        case LIME_COLOR:
            return out << "lime";

        case MAROON_COLOR:
            return out << "maroon";

        case NAVY_COLOR:
            return out << "navy";

        case OLIVE_COLOR:
            return out << "olive";

        case PURPLE_COLOR:
            return out << "purple";

        case RED_COLOR:
            return out << "red";

        case SILVER_COLOR:
            return out << "silver";

        case TEAL_COLOR:
            return out << "teal";

        case WHITE_COLOR:
            return out << "white";

        case YELLOW_COLOR:
            return out << "yellow";

        default:
            return out;
        }
    }

    Color3::Color3(ColorName name) :
        red(namedColors[3 * int(name) + 0]),
        green(namedColors[3 * int(name) + 1]),
        blue(namedColors[3 * int(name) + 2])
    { }

    ColorName Color3::name() const
    {
        int result = 0;
        int minDistance = squaredDistance(*this, Color3(ColorName(result)));
        for (int i = 1; i < COLOR_COUNT; ++i) {
            int distance = squaredDistance(*this, Color3(ColorName(i)));
            if (distance < minDistance) {
                result = i;
                minDistance = distance;
            }
        }
        return ColorName(result);
    }

    std::ostream &operator<<(std::ostream &out, Color3 const &color)
    {
        char buffer[8];
        sprintf(buffer, "#%02x%02x%02x", int(color.red), int(color.green),
                int(color.blue));
        return out << buffer;
    }
}
