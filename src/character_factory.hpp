#ifndef MONOMI_CHARACTER_FACTORY_HPP
#define MONOMI_CHARACTER_FACTORY_HPP

#include <boost/shared_ptr.hpp>

namespace monomi {
    class CharacterActor;
    class CharacterType;

    class CharacterFactory {
    public:
        CharacterFactory();

        boost::shared_ptr<CharacterActor> createNinja();
        boost::shared_ptr<CharacterActor> createSamurai();
        boost::shared_ptr<CharacterActor> createEarthMaster();
        boost::shared_ptr<CharacterActor> createFireMaster();
        boost::shared_ptr<CharacterActor> createAirMaster();
        boost::shared_ptr<CharacterActor> createWaterMaster();
        boost::shared_ptr<CharacterActor> createVoidMaster();

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
