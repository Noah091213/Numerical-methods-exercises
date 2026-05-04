#include <cmath>
#include <vector>
#include <iostream>
#include <iomanip>


std::vector<double> rhsSolver(double t, std::vector<double> v) {
    std::vector<double> result;

    result.push_back(std::exp(-t) * std::cos(v[1]) + std::pow(v[2], 2) - v[0]);
    result.push_back(std::cos(std::pow(v[2], 2)) - v[1]);
    result.push_back(std::cos(t) * std::exp(-std::pow(v[0], 2)) - v[2]);

    return result;
}

std::vector<double> trapFunc(double minT, double maxT, std::vector<double> v, double n) {
    double h = (maxT-minT)/n;   // Stepsize
    double t = minT;
    //std::vector<double> currentDvDt;

    for (int i = 0; i < n; i++) {   // Run for n iterations

        std::vector<double> currentDvDt = rhsSolver(t, v);
        std::vector<double> guessDvDt(3);

        for (int i = 0; i < 3; i++) {
            guessDvDt[i] = v[i] + h * currentDvDt[i]; 
        }

        std::vector<double> actualDvDt = rhsSolver(t+h, guessDvDt);

        for (int i = 0; i < 3; i++) {
            v[i] = v[i] + (h/2) * (currentDvDt[i] + actualDvDt[i]);
        }
        
        t+=h;
    }

    return v;
}



int main() {  

    std::cout << "\nExerise 1: \n" << std::endl;

    // Variable definition
    double t = 0.0;
    std::vector<double> v = {1.0, 2.0, 3.0};
    std::vector<double> res;

    res = rhsSolver(t, v); // Use the function to get results for t = 0

    std::cout << std::fixed << std::setprecision(6) << // Print the result to commandline
    " v1'(0) =  "  << res[0] << 
    "\n v2'(0) = " << res[1] <<
    "\n v3'(0) = " << res[2] << std::endl;

    std::cout << "\nExerise 2: \n" << std::endl;

    std::vector<double> nList = {50, 100, 200, 400, 800};   // Vector of N values to test

    for (int i = 0; i < nList.size(); i++) {    // Loop through all the N values and test them
        std::vector<double> resToPrint = trapFunc(0, 5, v, nList[i]);   // Use the trapFunc funtion to get the result with the given N value
        std::cout << "N = "<< std::setprecision(0) << nList[i] << std::setprecision(6) <<  " (" << resToPrint[0] << ", " << resToPrint[1] << ", " << resToPrint[2] << ")" << std::endl; // Print said result
    }



    return 0;
}