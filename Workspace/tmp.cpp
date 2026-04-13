#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>

// Define the function to integrate
double f(double x) {
    // Open rule avoids x=0, so sqrt(x) is safe
    return (std::cos(std::pow(x, 3)) * std::exp(-x)) / std::sqrt(x);
}

double extendedMidpoint(double a, double b, int M) {
    double h = (b - a) / M;
    double sum = 0.0;
    for (int j = 1; j <= M; ++j) {
        double midpoint = a + (j - 0.5) * h;
        sum += f(midpoint);
    }
    return h * sum;
}

int main() {
    double a = 0.0, b = 4.0;
    double tolerance = 1e-3;
    
    double prev_integral = 0.0;
    bool first_run = true;

    std::cout << std::setw(10) << "N" << " | " 
              << std::setw(15) << "Result" << " | " 
              << std::setw(15) << "Accuracy" << " | " 
              << "f-comps" << std::endl;
    std::cout << std::string(55, '-') << std::endl;

    // Start with M = 2^0 = 1 (which corresponds to N=2)
    for (int k = 0; k <= 20; ++k) {
        int M = std::pow(2, k);
        int N = M + 1;
        double current_integral = extendedMidpoint(a, b, M);

        if (!first_run) {
            double accuracy = std::abs(current_integral - prev_integral);
            std::cout << std::setw(10) << N << " | " 
                      << std::setw(15) << std::fixed << std::setprecision(8) << current_integral << " | " 
                      << std::setw(15) << std::scientific << accuracy << " | " 
                      << M << std::endl;

            if (accuracy < tolerance) break;
        } else {
            std::cout << std::setw(10) << N << " | " 
                      << std::setw(15) << std::fixed << std::setprecision(8) << current_integral << " | " 
                      << std::setw(15) << "---" << " | " 
                      << M << std::endl;
            first_run = false;
        }
        prev_integral = current_integral;
    }

    return 0;
}