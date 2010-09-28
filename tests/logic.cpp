#include "figure.h"

#include "figure.h"
#include "figure_iter.h"
#include <iostream>

int main() {
    std::cout << "testing:" << std::endl;
    Figure f(0,0, 0,1, 0,2, 0,3, 0,1, 2);
    LPlace p;
    p.x = 2;
    p.y = 0;
    for(Figure_iter fi(f); fi(); ++fi) {
        LPlace q(*fi);
        std::cout << "val: " << q.x << " " << q.y << std::endl;
    }
    return 0;
}
