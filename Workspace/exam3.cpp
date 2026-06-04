#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <vector>



// Parameter init, needed in multiple functions, so they are global
const double m = 1.0;             // Mass of the pendulum
const double L = 0.5;             // Length of the rod
const double g = 9.81;            // Gravity
const double kD = 0.2;            
const double omega = 100.0;       
const double A = 0.05;  



double getAccel(double t, double theta, double thetaDot) {
    double sec1 = -g / L;
    double sec2 = (A * pow(omega, 2)) / (m * L) * sin(omega * t);
    double sec3 = cos(theta);
    double sec4 = kD * thetaDot * std::abs(thetaDot);

    return ((sec1 + sec2) * sec3 - sec4);
}



double ODEmidpoint(double N, double tStart, double tEnd, double theta, double thetaDot) {
    double tInternal = tStart;
    double thetaInternal = theta;
    double thetaDotInternal = thetaDot;
    double h = (tEnd - tStart) / N;

    std::ofstream graphData;
    graphData.open("graphingData.csv");
    graphData << "t, theta\n";
    
    for (int i = 0; i < N; ++i) {
        if (i % 10 == 0) {
            graphData << tInternal << "," << thetaInternal << "\n";
        }
        
        double k1Theta      = thetaDotInternal;
        double k1ThetaDot   = getAccel(tInternal, thetaInternal, thetaDotInternal);

        double tMid         = tInternal + 0.5 * h;
        double thetaMid     = thetaInternal + 0.5 * h * k1Theta;
        double thetaDotMid  = thetaDotInternal + 0.5 * h * k1ThetaDot;

        double k2Theta      = thetaDotMid;
        double k2ThetaDot   = getAccel(tMid, thetaMid, thetaDotMid);

        thetaInternal += h * k2Theta;
        thetaDotInternal += h * k2ThetaDot;
        tInternal += h; 
    }
    graphData << tInternal << "," << thetaInternal << "\n";
    graphData.close();

    return thetaInternal;
}



void printTable(int runNumber, int N, double res, double accuracy) {
    std::cout << "| " << std::setw(3) << runNumber  << " | " << std::setw(14) << N << " | " << std::setw(14) << std::setprecision(10) << res << " | " ;
    if (accuracy != MAXFLOAT) {
        std::cout << std::setw(14) << std::setprecision(8) << accuracy << " |" << std::endl;
    } else {
        std::cout << std::setw(14) << "" << " |" << std::endl;;
    }
}



int main() {
    // Start conditions
    double t = 10.0;            
    double theta = 1.1;         // y1 
    double thetaDot = -0.1;    // y2

//======================================================================================

    std::cout << "Part 2\n" << std::endl;

    std::cout << std::fixed << std::setprecision(10);
    std::cout << "thetaDoubleDot(10) = " << getAccel(t, theta, thetaDot) << std::endl;

//======================================================================================

    std::cout << "\nPart 3\n" << std::endl;

    std::cout << "theta(20) = " << ODEmidpoint(100000, t, 20, theta, thetaDot) << std::endl;

//======================================================================================

    std::cout << "\nPart 4\n" << std::endl;

    std::cout << "| " << std::setw(3) << "Try" << " | " << std::setw(14) << "N" << " | " << std::setw(14) << "Result" << " | " << std::setw(14) << "Accuracy" << " |" << std::endl;

    int NtoTest = 1000;
    double minAccuracy = 1e-5;
    std::vector<double> results;

    for (int k = 1; k <= 25; ++k) {
        results.push_back(ODEmidpoint(NtoTest, t, 20, theta, thetaDot));

        double accuracy = MAXFLOAT;

        if (results.size() >= 2) {
            accuracy = std::abs((results[1] - results[0])/ 3.0);
            results.erase(results.begin());
        }

        printTable(k, NtoTest, results[0], accuracy);

        if (accuracy <= minAccuracy) {
            std::cout << "\nAccuracy threshold reached at N = " << NtoTest << std::endl;
            break;
        }
        NtoTest *= 2;

    }

    return 0;
}