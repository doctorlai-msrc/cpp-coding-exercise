#include <iostream>
#include <string>
#include <string_view>
#include <functional>
#include <ranges>

using pair = std::pair<size_t, char>;

void
default_callback(pair p)
{
    std::cout << "Index: " << p.first << ", Character: " << p.second << '\n';
}

void
enumerate(std::string_view str, std::function<void(pair)> callback = nullptr)
{
    for (const auto& [index, character] : std::views::zip(std::views::iota(0), str)) {
        callback({index, character});
    }
}

int
main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <string1> <string2> ...\n";
        enumerate("default string", default_callback);
        // make pipeline happy
        return 0;
    }
    for (int i = 1; i < argc; ++i) {
        std::string_view input = argv[i];
        std::cout << "Enumerating string: " << input << '\n';
        enumerate(input, [](pair p) { std::cout << "Index: " << p.first << ", Character: " << p.second << '\n'; });
    }
    return 0;
}
