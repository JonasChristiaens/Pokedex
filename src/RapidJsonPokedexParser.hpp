#pragma once

#include "IPokedexParser.hpp"

class RapidJsonPokedexParser : public IPokedexParser {
public:
	PokedexModel parse(std::ifstream& input) override;
};