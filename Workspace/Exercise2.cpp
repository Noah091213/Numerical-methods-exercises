#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>


double f(double x){
    return (cos(pow(x, 3)) * exp(-x)) / (sqrt(x));
}


double extendedMidpoint(double a, double b, double N) {
    double h=(b-a)/N-1;
    double totalSum = 0;

    for (int i; i <= N-1; i++ ) {
        totalSum += f(a + (i + 0.5) * h);   // f_k=f(a+kh)
    }

    return totalSum * h; // All the heights are added together previously, so to find the area we multiply by h (the width)
}



void printAccuracy(double runNumber, double N, double res, double accuracy, double fComp) {
    std::cout << "| " << std::setw(3) << runNumber << std::setw(8) << N << " | " << std::setw(10) << std::setprecision(8) << res << " | " << std::setw(10) << std::setprecision(8) << accuracy << " | " << std::setw(10) << fComp << " |" << std::endl;
}



int main() {
    

    std::cout << "| " << std::setw(3) << "Try" << " | " << std::setw(8) << "N" << " | " << std::setw(10) << "Result" << " | " << std::setw(10) << "Accuracy" << " | " << std::setw(10) << "FComps" << " |" << std::endl;
    std::vector<double> areaResults;

    for (int k = 0; k <= 200; ++k) {
        int computations = pow(2,k);
        int N = computations+1; // We need 1 more box then the amount of computations
        double a = 0;
        double b = 4;
        
        double result = extendedMidpoint(a,b,N);
        areaResults.push_back(result);

        double accuracy = 0;
        if (areaResults.size() <= 3) {
            double accuracy = (areaResults[0]-areaResults[1])/(areaResults[1]-areaResults[2]);
            areaResults.erase(areaResults.begin());
        } 
    
        double minAccuracy = pow(10,-3);

        printAccuracy(k, N, result, accuracy, computations);

        if (accuracy < minAccuracy) {
            break;
        }
    }


    return 0;
}