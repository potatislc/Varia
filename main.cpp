#include <iostream>
#include "using_varia.h"

func auto generic_noreturn(param auto test) {
    bool idk{std::is_assignable_v<int, decltype(test)>};
    std::cout << idk << '\n';
}

func auto generic_add(param auto a, param auto b) {
    return a + b;
}

varia_func generic_add2(auto a, auto b) {
    return a + b;
}

int main() {
    var a = 6;
    var a1 = 6.;
    a = a + a1;
    uint16_t hej = a1;
    var b = false;

    var c = "Ok";

    var d = "Hello, " + var("World!");
    d = "Nope!";
    d->shrink_to_fit();
    d += "SADJRKTEW";
    d = generic_add(d , c);
    var hmm = generic_add("King"s, "DX");
    generic_noreturn(4);

    var e = "Hello, "s + "World!";

    var f = var("Hello, ") + var("World!");

    String g;

    std::string test = d;

    std::cout << test << '\n';
    return 0;
}