#pragma once

#include "IPokedexParser.hpp"

class NlohmannPokedexParser : public IPokedexParser {
public:
	PokedexModel parse(std::ifstream& input) override;
};