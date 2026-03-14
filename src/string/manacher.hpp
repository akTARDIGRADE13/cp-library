#pragma once

#include <cassert>
#include <string>
#include <vector>

namespace akTARDIGRADE13 {

template <class T>
std::vector<int> manacher(const std::vector<T>& s) {
    int n = s.size();
    std::vector<int> ret(n << 1 | 1);
    int sz = ret.size();
    int i = 1, j = 1;
    while (i < sz) {
        while (j < i && i + j < (n << 1) && s[((i - j) >> 1) - 1] == s[(i + j) >> 1]) {
            j += 2;
        }
        ret[i] = j;
        if (j == 0) {
            i++;
            j = 1;
            continue;
        }
        int k = 1;
        while (k <= i && k + ret[i - k] < j) {
            ret[i + k] = ret[i - k];
            k++;
        }
        i += k;
        j -= k;
    }
    return ret;
}

std::vector<int> manacher(const std::string& s) {
    int n = s.size();
    std::vector<int> ret(n << 1 | 1);
    int sz = ret.size();
    int i = 1, j = 1;
    while (i < sz) {
        while (j < i && i + j < (n << 1) && s[((i - j) >> 1) - 1] == s[(i + j) >> 1]) {
            j += 2;
        }
        ret[i] = j;
        if (j == 0) {
            i++;
            j = 1;
            continue;
        }
        int k = 1;
        while (k <= i && k + ret[i - k] < j) {
            ret[i + k] = ret[i - k];
            k++;
        }
        i += k;
        j -= k;
    }
    return ret;
}

} // namespace akTARDIGRADE13
