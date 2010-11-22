#ifndef MONOMI_KEYS_HPP
#define MONOMI_KEYS_HPP

namespace monomi {
    namespace keys {
        enum Key {
            first,

            down,
            enter,
            escape,
            left,
            right,
            space,
            up,

            last
        };
    }
    
    using keys::Key;

    struct Modifiers {
        Modifiers();

        bool shift : 1;
        bool ctrl : 1;
        bool alt : 1;
        bool super : 1;
    };
}

#endif // MONOMI_KEYS_HPP
