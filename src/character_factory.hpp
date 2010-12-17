#ifndef MONOMI_CHARACTER_FACTORY_HPP
#define MONOMI_CHARACTER_FACTORY_HPP

#include <boost/shared_ptr.hpp>

namespace monomi {
    class Character;
    class CharacterType;

    class CharacterFactory {
    public:
        CharacterFactory();

        boost::shared_ptr<Character> createNinja();
        boost::shared_ptr<Character> createSamurai();
        boost::shared_ptr<Character> createEarthMaster();
        boost::shared_ptr<Character> createFireMaster();
        boost::shared_ptr<Character> createAirMaster();
        boost::shared_ptr<Character> createWaterMaster();
        boost::shared_ptr<Character> createVoidMaster();

    private:
        boost::shared_ptr<CharacterType> ninjaType_;
        boost::shared_ptr<CharacterType> samuraiType_;
        boost::shared_ptr<CharacterType> earthMasterType_;
        boost::shared_ptr<CharacterType> fireMasterType_;
        boost::shared_ptr<CharacterType> airMasterType_;
        boost::shared_ptr<CharacterType> waterMasterType_;
        boost::shared_ptr<CharacterType> voidMasterType_;
    };
}

#endif // MONOMI_CHARACTER_FACTORY_HPP
