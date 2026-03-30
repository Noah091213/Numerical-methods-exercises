#include "NR_C301/code/nr3.h"
#include "NR_C301/code/ludcmp.h"
#include "NR_C301/code/qrdcmp.h"
#include "NR_C301/code/roots_multidim.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

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

    VecDoub q(8);
    q[0] = L0;
    q[1] = L;
    q[2] = p;
    q[3] = x;
    q[4] = theta;
    q[5] = phi;
    q[6] = a;
    q[7] = H;

    VecDoub equations(8);
    equations[0] = a * (cosh(x/a) -1) -p;
    equations[1] = 2 * a * sinh(x/a) -L;
    equations[2] = 2 * x + 2 * k * cos(theta) -d;
    equations[3] = p + k * sin(theta) -n;
    equations[4] = sinh(x/a) -tan(phi);
    equations[5] = (1 + v/(w * L * a)) * tan(phi) -tan(theta);
    equations[6] = L0 * (1 + alpha * H) -L;
    equations[7] = (w * L0)/(2 * sin(phi))-H;

    

    return 0;
}

