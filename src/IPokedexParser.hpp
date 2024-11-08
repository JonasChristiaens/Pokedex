#pragma once

#include <string>
#include <vector>
#include <fstream>

struct PokemonEvolutionModel {
    std::string num;
    std::string name;
};

struct PokemonModel {
    int id;
    std::string num;
    std::string name;
    std::string img;

    std::vector<std::string> type;

    std::string height;
    std::string weight;

    std::vector<std::string> weaknesses;
};

struct PokedexModel {
    std::vector<PokemonModel> pokemon;
};

class IPokedexParser {
public:
    virtual PokedexModel parse(std::ifstream &input) = 0;
};
