#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

double f(double x) {
    double inner =  sin( -(x*x) + 5.0*x - 4.0);
    if (inner < 0.0) {
        inner = 0.0;    // This safety is necessary as because sqrt of 0 is impossible without complex numbers, resulting in nasty errors
    }
    
    return exp(2.0*x) * sqrt(inner);
}



double simpsonMethod(double a, double b, int n) {
    double h = (b-a) / n;
    double sum = f(a) + f(b);

    for (int i = 1; i < n; ++i) {
        double x = a + i * h;
        double weight;
        if (i % 2 == 0) {
            weight = 2.0;
        } 
        else {
            weight = 4.0;
        }
        sum += weight * f(x);
    }
    return (h/3.0) * sum;
}



double richardsonExtrapolation (double ah1, double ah2, double alphak) {
    return (alphak * ah2 - ah1) / (alphak - 1.0);
}



int main() {
    std::cout << "Exercise 4.2\n" << std::endl;

    double a = 1.0;
    double b = 4.0;
    double alpha = 2.0;
    std::vector<double> results;

    std::cout << std::fixed << std::setprecision(10);
    std::cout << " | " << std::setw(2) << "k" << " | " << std::setw(10) <<  "N" << " | " << std::setw(15) << "Integral Result" << " | " << std::setw(15) << "Richardson"<< " | " <<  std::setw(15) << "Error"<< " | " << std::setw(12) << "alpha^k" << " | " << std::endl;

    for (int k = 1; k <= 20; ++k) {
        int n = pow(2, k); // Number of intervals
        
        results.push_back(simpsonMethod(a, b, n));
        
        std::cout << " | " << std::setw(2) << k << " | " << std::setw(10) << n << " | " << std::setw(15) << results[k-1];
        
        if (k>2) {  // When 3 iterations are done, richardson extrapolation can be done:
            double kRich    = log2(std::abs((results[k-2] - results[k-3]) / (results[k-1] - results[k-2])));   // the result is going 1 further back than according to the formula, because k starts at 1, but the vector is 0 indexed
            double alphaK   = pow(alpha, kRich);
            double richRes  = richardsonExtrapolation(results[k-2], results[k-1], alphaK);
            double errEst   = std::abs(results[k-1]-richRes);
            
            std::cout << " | " << std::setw(15) << richRes << " | " << std::setw(15) << errEst << " | " << std::setw(12) << alphaK << " | " << std::endl;
        } 
        else {  // Without 3 iterations, Richardson cannot be done, N/A is finishing the table
            std::cout << " | " << std::setw(15) << "N/A" << " | " << std::setw(15) << "N/A" << " | " << std::setw(12) << "N/A" << " | " << std::endl;
        }
    }

    return 0;
}