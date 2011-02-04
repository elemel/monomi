#ifndef MONOMI_COLOR_HPP
#define MONOMI_COLOR_HPP

namespace monomi {
    class Color3 {
    public:
        float red;
        float green;
        float blue;

        Color3();
        Color3(float red, float green, float blue);
    };

    inline Color3::Color3() :
        red(0.0f), green(0.0f), blue(0.0f)
    { }

    inline Color3::Color3(float red, float green, float blue) :
        red(red), green(green), blue(blue)
    { }

    class Color4 {
    public:
        float red;
        float green;
        float blue;
        float alpha;

        Color4();
        Color4(float red, float green, float blue, float alpha = 1.0f);
    };

    inline Color4::Color4() :
        red(0.0f), green(0.0f), blue(0.0f), alpha(1.0f)
    { }

    inline Color4::Color4(float red, float green, float blue, float alpha) :
        red(red), green(green), blue(blue), alpha(alpha)
    { }
}

#endif // MOMOMI_COLOR_HPP
