#include "next_prime.h"
#include "determinant.h"
#include "factorial.h"

void test_next_prime() {
    static_assert(next_prime(1) == 2, "fail");
    static_assert(next_prime(2) == 2, "fail");
    static_assert(next_prime(9) == 11, "fail");
    static_assert(next_prime(17230) == 17231, "fail");
    static_assert(next_prime(121) == 127, "fail");
    static_assert(next_prime(1000000) == 1000003, "fail");
    static_assert(next_prime(1000000000) == 1000000007, "fail");
}

void test_factorial() {
    static_assert(Factorial<0>::value == 1, "fail");
    static_assert(Factorial<1>::value == 1, "fail");
    static_assert(Factorial<2>::value == 2, "fail");
    static_assert(Factorial<3>::value == 6, "fail");
    static_assert(Factorial<4>::value == 24, "fail");
    static_assert(Factorial<5>::value == 120, "fail");
    static_assert(Factorial<6>::value == 720, "fail");
    static_assert(Factorial<7>::value == 5040, "fail");
    static_assert(Factorial<8>::value == 40320, "fail");
    static_assert(Factorial<9>::value == 362880, "fail");
    static_assert(Factorial<10>::value == 3628800, "fail");
    static_assert(Factorial<11>::value == 39916800, "fail");
    static_assert(Factorial<12>::value == 479001600, "fail");
    static_assert(Factorial<13>::value == 6227020800, "fail");
}

void test_determinant() {
//     static_assert(determinant<2>({{{2, 3}, {1, 4}}}) == 5, "fail");
//     static_assert(determinant<3>({{{1,2,3},{4,5,6},{7,8,9}}}) == 0, "fail");
//     static_assert(determinant<1>({{{3}}}) == 3, "fail");
//     static_assert(determinant<5>({{
//         {3, -5, 1, -4, 2},
//         {-5, -4, -2, -3, -2},
//         {5, 3, 0, -3, -3},
//         {2, -2, 0, 2, -1},
//         {-1, -1, 5, -3, -5}
//     }}) == -7893, "fail");
}

int main ()
{
    test_next_prime();
    test_determinant();
    test_factorial();
}
