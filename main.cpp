#include "using_varia.h"
#include <vector>

int main() {
    var a = 34;
    var b = std::vector<int>();
    var c = false;
    var d = " Hej";
    d->shrink_to_fit();

    var x = 35678.3546785;
    var y = 5;
    var z = x + y;

    var h = "Hello, ";
    var w = "World!";
    var hw = h + w + d;

    return 0;
}