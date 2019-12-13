#include <iostream>

template <typename ... Args>
void variadic_function ()
{
    std::cout << "sizeof...(Args) = " << sizeof...(Args) << std::endl;
}

int main ()
{
    variadic_function<>();
    variadic_function<char>();
    variadic_function<char, int>();
    return 0;
}
