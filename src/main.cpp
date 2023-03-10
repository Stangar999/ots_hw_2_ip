#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <tuple>

#include "data_handler.h"
#include "print.h"
#include "read_input.h"


int main([[maybe_unused]] int argc, [[maybe_unused]] char const *argv[])
{
    try {
        const std::vector<std::vector<std::string>> v = ReadInput(std::cin);
        const std::vector<std::tuple<int, int, int, int>> ip_s = SelectIp(v);
        PrintRangesIp(std::pair{ip_s.cbegin(), ip_s.cend()});
        using it = decltype(ip_s.cbegin());
        PrintRangesIp(ApplyFilter<it, 0>(std::pair{ip_s.cbegin(), ip_s.cend()}, 1));
        PrintRangesIp(ApplyFilterRang(ip_s, 46));
        //PrintRangesIp(ApplyFilter<it, 0>(std::pair{ip_s.cbegin(), ip_s.cend()}, 46));
        PrintRangesIp(ApplyFilterTwo(std::pair{ip_s.cbegin(), ip_s.cend()}, 46, 70));
        //PrintRangesIp(ApplyFilter<it, 1>( ApplyFilter<it, 0>(std::pair{ip_s.cbegin(), ip_s.cend()}, 46),  70 ));
        PrintAllValue(ip_s, 46, std::index_sequence<0, 1, 2, 3>{});


    }
    catch(const std::invalid_argument &e) {
        std::cerr << e.what() << std::endl;
        std::cout << "invalid data" << std::endl;
    }
    catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
