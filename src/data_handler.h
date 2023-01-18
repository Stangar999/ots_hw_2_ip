#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <tuple>
#include <algorithm>
#include <ranges>

const size_t count_ip_bytes = 4;

static std::vector<std::string> split(const std::string &str, char d)
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

template<size_t N>
auto comp_ip_lower(std::tuple<int, int, int, int> tpl, int val) {
    return std::get<N>(tpl) > val;
}

template<size_t N>
auto comp_ip_upper(int val, std::tuple<int, int, int, int> tpl) {
    return std::get<N>(tpl) < val;
}

static std::vector<std::tuple<int, int, int, int>> SelectIp(const std::vector<std::vector<std::string>>& v){
    std::vector<std::tuple<int, int, int, int>> r;
    for (const auto& line : v)
    {
        r.push_back(vectorStrToTupleInt<count_ip_bytes>(split(line.at(0), '.')));
    }
    std::ranges::sort(r, std::ranges::greater());
    return r;
}

template<std::ranges::input_range R>
R ApplyFilterRang(R&& r, int val) {
    struct Comp {
    bool operator() ( int val, std::tuple<int, int, int, int> tpl ) const { return std::get<0>(tpl) < val; }
    bool operator() ( std::tuple<int, int, int, int> tpl, int val ) const { return val < std::get<0>(tpl); }
    };
    // TODO подскажите почему так не работает, ошибка компиляции, надо в main раскомментировать вызов
//    /home/kirill/Projects/Otus/ots_hw_2_ip/src/data_handler.h:66: ошибка: no match for call to ‘(const std::ranges::__equal_range_fn) (const std::vector<std::tuple<int, int, int, int> >&, int&, ApplyFilterRang<const std::vector<std::tuple<int, int, int, int> >&>(const std::vector<std::tuple<int, int, int, int> >&, int)::Comp)’
//    In file included from /home/kirill/Projects/Otus/ots_hw_2_ip/src/main.cpp:9:
//    /home/kirill/Projects/Otus/ots_hw_2_ip/src/data_handler.h: In instantiation of ‘R ApplyFilterRang(R&&, int) [with R = const std::vector<std::tuple<int, int, int, int> >&]’:
//    /home/kirill/Projects/Otus/ots_hw_2_ip/src/main.cpp:34:24:   required from here
//    /home/kirill/Projects/Otus/ots_hw_2_ip/src/data_handler.h:66:46: error: no match for call to ‘(const std::ranges::__equal_range_fn) (const std::vector<std::tuple<int, int, int, int> >&, int&, ApplyFilterRang<const std::vector<std::tuple<int, int, int, int> >&>(const std::vector<std::tuple<int, int, int, int> >&, int)::Comp)’
//       66 |         auto range = std::ranges::equal_range(r, val, Comp());
//          |                      ~~~~~~~~~~~~~~~~~~~~~~~~^~~~~~~~~~~~~~~~
    auto range = std::ranges::equal_range(r, val, Comp());
    return range;
}

template<typename It, size_t N>
std::pair<It, It> ApplyFilter(std::pair<It, It> p, int val) {
    struct Comp {
    bool operator() ( int val, std::tuple<int, int, int, int> tpl ) const { return std::get<N>(tpl) < val; }
    bool operator() ( std::tuple<int, int, int, int> tpl, int val ) const { return val < std::get<N>(tpl); }
    };

    auto [r_lower, r_upper] = std::equal_range(p.first, p.second, val, Comp());
    return std::make_pair(r_lower, r_upper);
}

template<typename It>
std::pair<It, It> ApplyFilterTwo(std::pair<It, It> p, int val_1, int val_2) {
    // TODO Помогите использовать шаблонную лямбду, не правильный синтаксис видиимо,а в интернете не смог найти, надо в main раскомментировать вызов
    [[maybe_unused]] auto comp_ip_upper_lamb = []<size_t N>(int val, std::tuple<int, int, int, int> tpl) {
        return std::get<N>(tpl) < val;
    };

    It lower_46 = std::lower_bound(p.first, p.second, val_1, comp_ip_lower<0>);
    It upper_46 = std::upper_bound(p.first, p.second, val_1, comp_ip_upper_lamb.template operator()<0>); // тут ошибку выдает, надо в main раскомментировать вызов
//    /home/kirill/Projects/Otus/ots_hw_2_ip/src/data_handler.h:96: ошибка: no matching function for call to ‘upper_bound(__gnu_cxx::__normal_iterator<const std::tuple<int, int, int, int>*, std::vector<std::tuple<int, int, int, int> > >&, __gnu_cxx::__normal_iterator<const std::tuple<int, int, int, int>*, std::vector<std::tuple<int, int, int, int> > >&, int&, <unresolved overloaded function type>)’
//    In file included from /home/kirill/Projects/Otus/ots_hw_2_ip/src/main.cpp:9:
//    /home/kirill/Projects/Otus/ots_hw_2_ip/src/data_handler.h: In instantiation of ‘std::pair<_FIter, _FIter> ApplyFilterTwo(std::pair<_FIter, _FIter>, int, int) [with It = __gnu_cxx::__normal_iterator<const std::tuple<int, int, int, int>*, std::vector<std::tuple<int, int, int, int> > >]’:
//    /home/kirill/Projects/Otus/ots_hw_2_ip/src/main.cpp:35:37:   required from here
//    /home/kirill/Projects/Otus/ots_hw_2_ip/src/data_handler.h:96:35: error: no matching function for call to ‘upper_bound(__gnu_cxx::__normal_iterator<const std::tuple<int, int, int, int>*, std::vector<std::tuple<int, int, int, int> > >&, __gnu_cxx::__normal_iterator<const std::tuple<int, int, int, int>*, std::vector<std::tuple<int, int, int, int> > >&, int&, <unresolved overloaded function type>)’
//       96 |     It upper_46 = std::upper_bound(p.first, p.second, val_1, comp_ip_upper_lamb.template operator()<0>);
//          |                   ~~~~~~~~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    It lower_46_70 = std::lower_bound(lower_46, upper_46, val_2, comp_ip_lower<1>);
    It upper_46_70 = std::upper_bound(lower_46, upper_46, val_2, comp_ip_upper_lamb.template operator()<1>); // тут ошибку выдает, надо в main раскомментировать вызов

    return std::make_pair(lower_46_70, upper_46_70);
}
