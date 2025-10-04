#include "using_varia.h"
#include <vector>

int main() {
    var a = 34;
    a = 7;
    var c = false;
    c = true;
    var d = " Hej";
    d = "Nej";
    d->shrink_to_fit();
    var e = none;
    e = none;

    var x = 35678.3546785;
    var y = 6 + x + 7;
    var z = x + y;
    x = none;

    var h = "Hello, ";
    var w = "World!";
    var hw = h + w + d;
    h = none;

    var tezt = none;

    std::cout << (h == none) << '\n'; // Should return true, but operator= for internal_type::Num is not overloaded yet
    std::cout << (tezt == none) << '\n';
    std::cout << (a == none) << '\n';

    return 0;
}