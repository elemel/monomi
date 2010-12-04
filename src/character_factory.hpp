#ifndef MONOMI_CHARACTER_FACTORY_HPP
#define MONOMI_CHARACTER_FACTORY_HPP

#include <memory>

namespace monomi {
    class Character;
    class CharacterType;

    class CharacterFactory {
    public:
        CharacterFactory();

        std::auto_ptr<Character> createNinja();
        std::auto_ptr<Character> createSamurai();
        std::auto_ptr<Character> createEarthMaster();
        std::auto_ptr<Character> createFireMaster();
        std::auto_ptr<Character> createAirMaster();
        std::auto_ptr<Character> createWaterMaster();
        std::auto_ptr<Character> createVoidMaster();

    private:
        std::auto_ptr<CharacterType> ninjaType_;
        std::auto_ptr<CharacterType> samuraiType_;
        std::auto_ptr<CharacterType> earthMasterType_;
        std::auto_ptr<CharacterType> fireMasterType_;
        std::auto_ptr<CharacterType> airMasterType_;
        std::auto_ptr<CharacterType> waterMasterType_;
        std::auto_ptr<CharacterType> voidMasterType_;
    };
}

#endif // MONOMI_CHARACTER_FACTORY_HPP
