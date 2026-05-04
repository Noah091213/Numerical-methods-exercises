#include <cmath>
#include <vector>
#include <iostream>
#include <iomanip>


std::vector<double> solver(double t, std::vector<double> v) {
    std::vector<double> result;

    result.push_back(std::exp(-t) * std::cos(v[1]) + std::pow(v[2], 2) - v[0]);
    result.push_back(std::cos(std::pow(v[2], 2)) - v[1]);
    result.push_back(std::cos(t) * std::exp(-std::pow(v[0], 2)) - v[2]);

    return result;
}


int main() {  

    double t = 0.0;
    std::vector<double> v = {1.0, 2.0, 3.0};
    std::vector<double> res;

    res = solver(t, v);

    std::cout << std::fixed << std::setprecision(6) << 
    " v1'(0) = "   << res[0] << 
    "\n v2'(0) = " << res[1] <<
    "\n v3'(0) = " << res[2] << std::endl;

    return 0;
}