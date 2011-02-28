#ifndef MONOMI_CHARACTER_CONFIG_LOADER_HPP
#define MONOMI_CHARACTER_CONFIG_LOADER_HPP

#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

namespace monomi {
    class GameLogic;

    class CharacterConfigLoader {
    public:
        CharacterConfigLoader(GameLogic &gameLogic);

        void load(std::string const &configName);

    private:
        GameLogic *gameLogic_;

        void loadCharacterType(std::string const &name,
                               boost::property_tree::ptree const &tree);
    };
}

#endif // MONOMI_CHARACTER_CONFIG_LOADER_HPP
