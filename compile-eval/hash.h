#pragma once
#include "another_pow.h"

constexpr int hashi(const char *s, int p, int index) {
    return *s * pow(p, index)
            + (*s ? hashi(s + 1, p, index + 1) : 0);
}

constexpr int hash(const char *s, int p, int mod) {
    return hashi(s, p, 0) % mod;
}

int RtHash (const char *s, int p, int mod) {

    int i = 0;
    int result = 0;

    while (*s) {
        result += (((*s++) % mod) * (pow(p, i++) % mod)) % mod;
    }

    return result % mod;
}
