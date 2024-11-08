#include <iostream>
#include <fstream>
#include <windows.h>

#if defined(JSON_LIBRARY_NLOHMANN)
#include "NlohmannPokedexParser.hpp"
using JsonPokedexParser = NlohmannPokedexParser;
#define PARSER_NAME "Nlohmann parser"

#elif defined(JSON_LIBRARY_RAPIDJSON)
#include "RapidJsonPokedexParser.hpp"
using JsonPokedexParser = RapidJsonPokedexParser;
#define PARSER_NAME "RapidJson parser"

#endif

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    #ifdef PARSER_NAME
    std::cout << "Using " << PARSER_NAME <<  "\n " << std::endl;
    #endif

    //Load Json
    std::ifstream input(".\\content\\pokedex.json");  // Open the file
    if (!input.is_open()) 
    {
        std::cout << "Failed to load json file!" << std::endl;
        return -1;
    }

    auto parser = JsonPokedexParser();

    auto pokedexModel = parser.parse(input);
    for(const auto& poke : pokedexModel.pokemon)
    {
        std::cout << poke.id << ". " << poke.name;
        std::cout << " [";
        for (size_t typeIdx{}; typeIdx < poke.type.size(); ++typeIdx)
        {
            std::cout << poke.type[typeIdx];
            if (typeIdx != poke.type.size() - 1)
            {
                std::cout << ", ";
            }
        }
        std::cout << "]" << std::endl;
    }

    return 0;
}