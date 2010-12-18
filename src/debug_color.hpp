#ifndef MONOMI_DEBUG_COLOR_HPP
#define MONOMI_DEBUG_COLOR_HPP

namespace monomi {
    class DebugColor {
    public:
        float red, green, blue;

        DebugColor();
        DebugColor(float red, float green, float blue);
    };

    namespace debugColors {
        DebugColor black();
        DebugColor blue();
        DebugColor cyan();
        DebugColor gray();
        DebugColor green();
        DebugColor lightBlue();
        DebugColor magenta();
        DebugColor red();
        DebugColor white();
        DebugColor yellow();
    }
}

#endif // MONOMI_DEBUG_COLOR_HPP
