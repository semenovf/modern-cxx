#include <algorithm>
#include <locale>
#include <iostream>

int main ()
{
    constexpr double pi {3.14159};

    for (std::string const & locname: {""
            , "en_US.UTF8"
            , "ru_RU.UTF8"
            , "fr_FR.UTF8"
            , "zu_ZA.UTF8"
    }) {
        try {
            std::locale locale{locname};
            std::cout.imbue(locale);
            std::cout << locale.name() << ": " << pi << std::endl;
        } catch (...) {
            std::cerr << "Locale " << locname << " failed\n";
        }
    }
}
