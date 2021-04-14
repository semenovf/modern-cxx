#pragma once

template <int x, int y0>
struct Sqrt1
{
    static const int value = (x == 0 || x == 1)
            ? x
            : ((y0 > x / y0)
                    ? Sqrt1<x, ((x / y0) + y0) / 2>::value
                    : y0);
};

template <int x>
struct Sqrt1<x, 0>
{
    static const int value = 0;
};

template <int x>
struct Sqrt
{
    static const int value = (x == 0 || x == 1)
            ? x
            : Sqrt1<x, x / 2>::value;
};

//
// https://overcoder.net/q/443238/бинарный-поиск-для-вычисления-квадратного-корня-java
//
// Runtime version of Sqrt
int RtSqrt (int x, int y0);

inline int RtSqrt (int x)
{
    // square roots of 0 and 1 are trivial and x / 2 for
    // the y0 parameter will cause a divide-by-zero exception
    if (x == 0 || x == 1) {
        return x;
    }
    // starting with x / 2 avoids overflow issues
    return RtSqrt (x, x / 2);
} // end intSqRootRecursive

inline int RtSqrt (int x, int y0)
{
    // square roots of 0 and 1 are trivial
    // y0 == 0 will cause a divide-by-zero exception
    if (x == 0 || x == 1) {
        return x;
    } // end if
    if (y0 > x / y0) {
        int y1 = ((x / y0) + y0) / 2;
        return RtSqrt(x, y1);
    } else {
        return y0;
    } // end if...else
} // end intSqRootRecursive

inline int RtSqrtV1 (int x)
{
    // square roots of 0 and 1 are trivial and
    // y == 0 will cause a divide-by-zero exception
    if (x == 0 || x == 1)
        return x;

    int y;

    // starting with y = x / 2 avoids overflow issues
    for (y = x / 2; y > x / y; y = ((x / y) + y) / 2);

    return y;
}
inline int RtSqrtV2 (int x)
{
    if (x == 0 || x == 1)
        return x;

    int start = 1, end = x / 2;

    while (start <= end) {
        int mid = start + (end - start) / 2;

        if(mid == x / mid)
            return mid;

        if(mid < x / mid)
            start = mid + 1;
        else
            end = mid - 1;
    }

    return start - 1;
}

