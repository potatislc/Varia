#include "using_varia.h"
#include <vector>

int main() {
    var a = 34;
    var c = false;
    var d = " Hej";
    d->shrink_to_fit();
    var e = none;

    var x = 35678.3546785;
    var y = 6 + x + 7;
    var z = x + y;

    var h = "Hello, ";
    var w = "World!";
    var hw = h + w + d;

    var tezt = none;

    std::cout << (e == none) << '\n'; // Should return true, but operator= for internal_type::Num is not overloaded yet
    std::cout << (tezt == none) << '\n';
    std::cout << (a == none) << '\n';

    return 0;
}