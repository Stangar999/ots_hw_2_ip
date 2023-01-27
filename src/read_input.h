#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "data_handler.h"

[[maybe_unused]] static std::vector<std::vector<std::string>> ReadInput(std::istream& in) {
    std::vector<std::vector<std::string> > r;
    for (std::string line; std::getline(in, line);)
    {
        r.emplace_back(Split(line, '\t'));
    }
    return r;
}
