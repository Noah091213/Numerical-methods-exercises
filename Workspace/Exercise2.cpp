#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include "NR_C301/code/nr3.h"
#include "NR_C301/code/quadrature.h"
#include "NR_C301/code/derule.h"

int deruleComputations = 0;

double f(double x, double del){
    ++deruleComputations;
    return (cos(pow(x, 3)) * exp(-x)) / (sqrt(x));
}


double extendedMidpoint(double a, double b, double N) {
    double h = (b-a)/(N-1);
    //std::cout << "h: " << h << std::endl; // Debug
    double totalSum = 0.0;

    for (int i = 0; i <= (N-1); i++ ) {
        totalSum += f(a +(i + 0.5) * h, 0);   // f_k=f(a+kh)
    }

    return totalSum * h; // All the heights are added together previously, so to find the area we multiply by h (the width)
}



void printTable(double runNumber, double N, double res, double accuracy, double fComp) {
    std::cout << "| " << std::setw(3) << runNumber  << " | " << std::setw(14) << N << " | " << std::setw(14) << std::setprecision(10) << res << " | " ;
    if (accuracy != MAXFLOAT) {
        std::cout << std::setw(14) << std::setprecision(8) << accuracy;
    } else {
        std::cout << std::setw(14) << "";
    }
    std::cout << " | " << std::setw(14) << fComp << " |" << std::endl;
}


int main() {    


    std::cout << "Exercise II \n" << std::endl;

    std::cout << "| " << std::setw(3) << "Try" << " | " << std::setw(14) << "N" << " | " << std::setw(14) << "Result" << " | " << std::setw(14) << "Accuracy" << " | " << std::setw(14) << "FComps" << " |" << std::endl;
    std::vector<double> areaResults = {};
    double minAccuracy = pow(10,-3);
    double a = 0.0;
    double b = 4.0;

    for (int k = 0; k <= 50; k++) {
        double computations = pow(2,k);
        double N = computations+1; // We need 1 more box then the amount of computations
        
        double result = extendedMidpoint(a,b,N);
        areaResults.push_back(result);

        double accuracy = MAXFLOAT;
    
        if (areaResults.size() >= 3) {
            //std::cout << "Current result: " << areaResults[2] << " Previous result: " << areaResults[1] << " first result: " << areaResults[0] << std::endl;
            
            double ak = (areaResults[0]-areaResults[1])/(areaResults[1]-areaResults[2]);    // Find a^k
            accuracy = std::abs((areaResults[1]-areaResults[0])/(ak-1));                    // Then find the actual accuracy
            //std::cout << "aK: " << ak << " Accuracy: " << accuracy << std::endl;
            
            areaResults.erase(areaResults.begin()); // Remove the oldest calculation
        } 

        printTable(k+1, N, result, accuracy, computations);

        if (accuracy <= minAccuracy) {
            break;
        }
    }

    std::cout << "\nExercise III \n" << std::endl;

    deruleComputations = 0;
    DErule<double(double, double)> deruleObj(f, a, b);
    vector<double> deruleResults = {};

    std::cout << "| " << std::setw(3) << "Try" << " | " << std::setw(14) << "N" << " | " << std::setw(14) << "Result" << " | " << std::setw(14) << "Accuracy" << " | " << std::setw(14) << "FComps" << " |" << std::endl;
    
    for (int i = 0; i <= 50; i++) {
        double currentResult = deruleObj.next();
        deruleResults.push_back(currentResult);
        double deruleAccuracy = MAXFLOAT;

        if (deruleResults.size() >= 3) {
            
            double ak = (deruleResults[0]-deruleResults[1])/(deruleResults[1]-deruleResults[2]);    // Find a^k
            deruleAccuracy = std::abs((deruleResults[1]-deruleResults[0])/(ak-1));                    // Then find the actual accuracy
            
            deruleResults.erase(deruleResults.begin()); // Remove the oldest calculation
        } 

        printTable(i+1, 0, currentResult, deruleAccuracy, deruleComputations);

        if (deruleAccuracy <= minAccuracy) {
            break;
        }
    }

    return 0;
}