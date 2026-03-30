#include "NR_C301/code/nr3.h"
#include "NR_C301/code/ludcmp.h"
#include "NR_C301/code/qrdcmp.h"
#include "NR_C301/code/roots_multidim.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>


struct vectorFunction {
    
    double n, d, v, k, w, alpha;
    vectorFunction(double vv, double kk, double ww, double aalpha, double dd, double nn): v(vv), k(kk), w(ww), alpha(aalpha), d(dd), n(nn) {}

    VecDoub operator () (VecDoub_I q){
        VecDoub equations(8);
        equations[0] = q[6] * (cosh(q[3]/q[6]) -1) -q[2];
        equations[1] = 2 * q[6] * sinh(q[3]/q[6]) -q[1];
        equations[2] = 2 * q[3] + 2 * k * cos(q[4]) -d;
        equations[3] = q[2] + k * sin(q[4]) -n;
        equations[4] = sinh(q[3]/q[6]) -tan(q[5]);
        equations[5] = (1 + v/(w * q[1] * q[6])) * tan(q[5]) -tan(q[4]);
        equations[6] = q[0] * (1 + alpha * q[7]) -q[1];
        equations[7] = (w * q[0])/(2 * sin(q[5])) -q[7];
        return equations;
    }

};

int main() {    

    double v     = 120; // Insulators weight in kg
    double k     = 2.5; // length of insulators
    double w     = 4.0; // Weight of cable kg pr m, when resting
    double alpha = 2*pow(10,-7);   // Elasticity coefficient of cable 
    
    double d;       // Distance
    double L0;      // Resting length
    double L;       // Suspended length of the cable
    double n;       // Sagging of cable from the insulators attachement points
    double p;       // Sagging of cable from the cables attachment points
    double x;       // half the distance between the cables attachment points
    double theta;   // Angle between insulator and horizontal plane at attachment points
    double phi;     // Angle between cable and horizontal plane at attachment point
    double a;       // Parameter in the catenary equation for the cable
    double H;       // String tension in the cable

    bool statusBool;

    std::vector<double> nValues = {5, 2, 1, 0.5, 0.2, 0.1};

    for (int i = 0; i< nValues.size(); i++) {
        
        VecDoub q(8);
        q[0] = L0;
        q[1] = L;
        q[2] = p;
        q[3] = x;
        q[4] = theta;
        q[5] = phi;
        q[6] = a;
        q[7] = H;

        vectorFunction F(v,k,w,alpha,d,n);
        newt(q, statusBool, F);

        // Safety check
        if (statusBool == true) {
            std::cout << "Checked n = " << nValues[i] << " and a solution could not be found" << std::endl;
        } else {
            std::cout << "Checked n = " << nValues[i] << std::endl;
            std::cout << "Cable length at resting position = " << std::endl;
            std::cout << "String tension in cable at resting = " << std::endl; 
        }
    }

    return 0;
}

