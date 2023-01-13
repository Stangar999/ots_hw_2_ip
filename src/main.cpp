#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <tuple>
#include <algorithm>

const size_t count_ip_bytes = 4;

std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

template <std::size_t... N>
auto vectorStrToTupleIntHelper(const std::vector<std::string>& v, std::index_sequence<N...>) {
  return std::make_tuple(stoi(v[N])...);
}

template <size_t N>
auto vectorStrToTupleInt(const std::vector<std::string>& v) {
    assert(N <= v.size());
    return vectorStrToTupleIntHelper(v, std::make_index_sequence<N>());
}

void PrintIp(const std::tuple<int, int, int, int>& ip) {
    std::cout << std::get<0>(ip) << "." << std::get<1>(ip) << "." << std::get<2>(ip) << "." << std::get<3>(ip) << '\n';
}

template <typename It>
void PrintRanges(const It lower, const It upper) {
    for (auto ip = lower; ip != upper; ++ip)
    {
        PrintIp(*ip);
    }
}

// TODO_2 можно ли написать лямбду с заменяющую такую шаблоную функцию c шаблонным аргументом-константой
template<size_t N>
auto comp_ip_lower(std::tuple<int, int, int, int> tpl, int val) {
    return std::get<N>(tpl) > val;
}
template<size_t N>
auto comp_ip_upper(int val, std::tuple<int, int, int, int> tpl) {
    return std::get<N>(tpl) < val;
}

template <typename Cont, typename T, size_t... N>
void PrintAllValue(const Cont &cont, T val, std::index_sequence<N...>) {
    std::ranges::for_each(cont, [val](const auto &lth) {
        if ( (... || (std::get<N>(lth) == val)) ){
            PrintIp(lth);
        } });
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char const *argv[])
{
    try {
        const std::vector<std::tuple<int, int, int, int>> ip_pool = std::invoke([]()
        {
            std::vector<std::tuple<int, int, int, int>> ip_pool;
            for (std::string line; std::getline(std::cin, line);)
            {
                std::vector<std::string> v = split(line, '\t');
                ip_pool.push_back(vectorStrToTupleInt<count_ip_bytes>(split(v.at(0), '.')));
            }
            std::ranges::sort(ip_pool, std::ranges::greater());
            return ip_pool;
        });

        PrintRanges(ip_pool.begin(), ip_pool.end());

        {
            // TODO_1 можно ли написать лямбду заменяющую такой функтор (перегрузка () для equal_range)
            struct Comp {
            bool operator() ( int val, std::tuple<int, int, int, int> tpl ) const { return std::get<0>(tpl) < val; }
            bool operator() ( std::tuple<int, int, int, int> tpl, int val ) const { return val < std::get<0>(tpl); }
            };

            auto [lower, upper] = std::equal_range(ip_pool.begin(), ip_pool.end(), 1, Comp());
            PrintRanges(lower, upper);
        }

        {
            auto lower_46 = std::lower_bound(ip_pool.cbegin(), ip_pool.cend(), 46, comp_ip_lower<0>);
            auto upper_46 = std::upper_bound(ip_pool.cbegin(), ip_pool.cend(), 46, comp_ip_upper<0>);

            auto lower_46_70 = std::lower_bound(lower_46, upper_46, 70, comp_ip_lower<1>);
            auto upper_46_70 = std::upper_bound(lower_46, upper_46, 70, comp_ip_upper<1>);
            PrintRanges(lower_46_70, upper_46_70);
        }

        PrintAllValue(ip_pool, 46, std::index_sequence<0, 1, 2, 3>{});
    }
    catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
