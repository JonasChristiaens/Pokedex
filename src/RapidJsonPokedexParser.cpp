#include "RapidJsonPokedexParser.hpp"

#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/encodedstream.h>

PokedexModel RapidJsonPokedexParser::parse(std::ifstream& input)
{
    rapidjson::IStreamWrapper streamWrapper(input);
    rapidjson::EncodedInputStream<rapidjson::UTF8<> , rapidjson::IStreamWrapper> encodedStreamWrapper(streamWrapper);

    rapidjson::Document document;
    document.ParseStream(encodedStreamWrapper);

    PokedexModel result;

    auto &pokemonJson = document["pokemon"].GetArray();
    for (const auto &pokeJson : pokemonJson) {
        auto &poke = result.pokemon.emplace_back();
        poke.id = pokeJson["id"].GetInt();
        poke.num = pokeJson["num"].GetString();
        poke.name = pokeJson["name"].GetString();

        const auto &typeJson = pokeJson["type"].GetArray();
        for (const auto &type : typeJson) {
            poke.type.push_back(type.GetString());
        }

        poke.height = pokeJson["height"].GetString();
        poke.weight = pokeJson["weight"].GetString();

        const auto &weaknessJson = pokeJson["weaknesses"].GetArray();
        for (const auto &weakness : weaknessJson) {
            poke.weaknesses.push_back(weakness.GetString());
        }
    }

    return result;
}
