#include "Minkowski_Sum.cpp"
double ConvexHullDist(vector<pdd> A, vector<pdd> B) {
    for (auto &p : B) p = {-p.F, -p.S};
    auto C = Minkowski(A, B); // assert (int)C.size() > 0
    if (PointInConvex(C, pdd(0, 0))) return 0;
    double ans = PointSegDist(C.back(), C[0], pdd(0, 0));
    for (int i = 0; i + 1 < (int)C.size(); ++i) {
        ans = min(ans, PointSegDist(C[i], C[i + 1], pdd(0, 0)));
    }
    return ans;
}
