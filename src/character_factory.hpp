#ifndef MONOMI_CHARACTER_FACTORY_HPP
#define MONOMI_CHARACTER_FACTORY_HPP

#include "character_tag.hpp"

#include <vector>
#include <boost/array.hpp>
#include <boost/shared_ptr.hpp>

namespace monomi {
    class CharacterActor;
    class CharacterType;

    class CharacterFactory {
    public:
        CharacterFactory();

        boost::shared_ptr<CharacterActor> create(CharacterTag tag) const;

    private:
        typedef boost::shared_ptr<CharacterType> TypePtr;
        typedef boost::array<TypePtr, characterTagCount> TypeArray;

        TypeArray types_;
    };
}

#endif // MONOMI_CHARACTER_FACTORY_HPP
