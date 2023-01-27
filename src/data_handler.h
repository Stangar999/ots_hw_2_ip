#pragma once

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <tuple>
#include <algorithm>
#include <ranges>

const size_t kCountIpBytes = 4;

namespace{

std::vector<std::string> Split(const std::string &str, char d)
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
auto FromVectorStrToTupleIntHelper(const std::vector<std::string>& v, std::index_sequence<N...>) {
  return std::make_tuple(stoi(v[N])...);
}

template <size_t N>
auto FromVectorStrToTupleInt(const std::vector<std::string>& v) {
    assert(N <= v.size());
    return FromVectorStrToTupleIntHelper(v, std::make_index_sequence<N>());
}

template<size_t N>
auto CompIpLower(std::tuple<int, int, int, int> tpl, int val) {
    return std::get<N>(tpl) > val;
}

template<size_t N>
auto CompIpUpper(int val, std::tuple<int, int, int, int> tpl) {
    return std::get<N>(tpl) < val;
}

[[maybe_unused]] std::vector<std::tuple<int, int, int, int>> SelectIp(const std::vector<std::vector<std::string>>& v){
    std::vector<std::tuple<int, int, int, int>> r;
    for (const auto& line : v)
    {
        r.push_back(FromVectorStrToTupleInt<kCountIpBytes>(Split(line.at(0), '.')));
    }
    std::ranges::sort(r, std::ranges::greater());
    return r;
}

template<std::ranges::input_range R>
auto ApplyFilterRang(R&& r, int val) {
    struct Comp {
    bool operator() ( int val1, int val2 ) const { return val1 < val2; }
    bool operator() ( std::tuple<int, int, int, int> tpl1, std::tuple<int, int, int, int> tpl2 ) const { return tpl1 < tpl2; }
    bool operator() ( int val, std::tuple<int, int, int, int> tpl ) const { return std::get<0>(tpl) < val; }
    bool operator() ( std::tuple<int, int, int, int> tpl, int val ) const { return val < std::get<0>(tpl); }
    };

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
    [[maybe_unused]] auto comp_ip_upper_lamb = []<size_t N>(int val, std::tuple<int, int, int, int> tpl) {
        return std::get<N>(tpl) < val;
    };

    It lower_46 = std::lower_bound(p.first, p.second, val_1, CompIpLower<0>);
    auto invoker0 = [&comp_ip_upper_lamb](auto... args) { return comp_ip_upper_lamb.template operator()<0>(args...); };
    It upper_46 = std::upper_bound(p.first, p.second, val_1, invoker0);

    It lower_46_70 = std::lower_bound(lower_46, upper_46, val_2, CompIpLower<1>);
    auto invoker1 = [&comp_ip_upper_lamb](auto... args) { return comp_ip_upper_lamb.template operator()<1>(args...); };
    It upper_46_70 = std::upper_bound(lower_46, upper_46, val_2, invoker1);

    return std::make_pair(lower_46_70, upper_46_70);
}

}
