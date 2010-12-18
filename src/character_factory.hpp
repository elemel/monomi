#ifndef MONOMI_CHARACTER_FACTORY_HPP
#define MONOMI_CHARACTER_FACTORY_HPP

#include "character_tag.hpp"

#include <boost/shared_ptr.hpp>
#include <boost/unordered_map.hpp>

namespace monomi {
    class CharacterActor;
    class CharacterType;

    class CharacterFactory {
    public:
        CharacterFactory();

        boost::shared_ptr<CharacterActor> create(CharacterTag tag) const;

    private:
        typedef boost::shared_ptr<CharacterType> TypePtr;
        typedef boost::unordered_map<CharacterTag, TypePtr> TypeMap;
        typedef TypeMap::const_iterator TypeConstIterator;

        TypeMap types_;
    };
}

#endif // MONOMI_CHARACTER_FACTORY_HPP
