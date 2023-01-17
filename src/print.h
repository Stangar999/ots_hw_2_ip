#include <iostream>
#include <tuple>
#include <algorithm>

void PrintIp(const std::tuple<int, int, int, int>& ip) {
    std::cout << std::get<0>(ip) << "." << std::get<1>(ip) << "." << std::get<2>(ip) << "." << std::get<3>(ip) << '\n';
}

template <typename It>
void PrintRangesIp(const It lower, const It upper) {
    for (auto ip = lower; ip != upper; ++ip)
    {
        PrintIp(*ip);
    }
}

template <typename It>
void PrintRangesIp(std::pair<It, It> p) {
    for (auto ip = p.first; ip != p.second; ++ip)
    {
        PrintIp(*ip);
    }
}

template <typename Cont, typename T, size_t... N>
void PrintAllValue(const Cont &cont, T val, std::index_sequence<N...>) {
    std::ranges::for_each(cont, [val](const auto &lth) {
        if ( (... || (std::get<N>(lth) == val)) ){
            PrintIp(lth);
        } });
}
