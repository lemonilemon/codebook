#include "include/common.h"
double factor = 100000;
const int base = 1e9; // remember to run ~ 10 times
for (int it = 1; it <= 1000000; ++it) {
    // ans: answer, nw: current value
    if (exp(-(nw - ans) / factor) >= (double)(rd() % base) / base)
        ans = nw;
    factor *= 0.99995;
}
