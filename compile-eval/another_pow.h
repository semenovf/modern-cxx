#pragma once

constexpr int pow(int a, int b) {
    return b > 0 ? static_cast<int>(a * pow(a, b - 1)) : 1;
}
