#include "debug_color.hpp"

namespace monomi {
    DebugColor::DebugColor() :
        red(0.0f),
        green(0.0f),
        blue(0.0f)
    { }

    DebugColor::DebugColor(float red, float green, float blue) :
        red(red),
        green(green),
        blue(blue)
    { }

    namespace debugColors {
        DebugColor black()
        {
            return DebugColor(0.0f, 0.0f, 0.0f);
        }

        DebugColor blue()
        {
            return DebugColor(0.0f, 0.0f, 1.0f);
        }

        DebugColor cyan()
        {
            return DebugColor(0.0f, 1.0f, 1.0f);
        }

        DebugColor gray()
        {
            return DebugColor(0.5f, 0.5f, 0.5f);
        }

        DebugColor green()
        {
            return DebugColor(0.0f, 1.0f, 0.0f);
        }

        DebugColor lightBlue()
        {
            return DebugColor(0.0f, 0.5f, 1.0f);
        }

        DebugColor red()
        {
            return DebugColor(1.0f, 0.0f, 0.0f);
        }

        DebugColor magenta()
        {
            return DebugColor(1.0f, 0.0f, 1.0f);
        }

        DebugColor white()
        {
            return DebugColor(1.0f, 1.0f, 1.0f);
        }

        DebugColor yellow()
        {
            return DebugColor(1.0f, 1.0f, 0.0f);
        }
    }
}
