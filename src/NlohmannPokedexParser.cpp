#include "NlohmannPokedexParser.hpp"

#include <nlohmann/json.hpp>

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(PokemonEvolutionModel, 
    num,
    name
);
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(PokemonModel,
    id,
    num,
    name,
    img,

    type,

    height,
    weight,

    weaknesses
);
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(PokedexModel,
    pokemon
);

PokedexModel NlohmannPokedexParser::parse(std::ifstream& input)
{
    auto json = nlohmann::json::parse(input);

    PokedexModel result;
    json.get_to(result);

    return result;
}
