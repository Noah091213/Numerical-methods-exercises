#include <iostream>
#include <cmath>
#include <iomanip>
#include "NR_C301/code/nr3.h"


double f(double x) {
    return (3.0*x*pow(cos(x),3) - 0.2*exp(pow(x,2)) + 0.7);
}


template <class T>
Doub riddersMethod(T &func, const Doub x1, const Doub x2, const Doub xacc, int iterationCount) {   
    // This is a modified version of the numerical recipies version
	Doub fl=func(x1);
	Doub fh=func(x2);
	if ((fl > 0.0 && fh < 0.0) || (fl < 0.0 && fh > 0.0)) {
		Doub xl=x1;
		Doub xh=x2;
		Doub ans=-9.99e99;
		for (Int j=0; j < iterationCount; j++) {// Set to only run for the number of iterations needed, instead of to max
			Doub xm=0.5*(xl+xh);
			Doub fm=func(xm);
			Doub s=sqrt(fm*fm-fl*fh);
			if (s == 0.0) return ans;
			Doub xnew=xm+(xm-xl)*((fl >= fh ? 1.0 : -1.0)*fm/s);
			if (abs(xnew-ans) <= xacc) return ans;
			ans=xnew;
			Doub fnew=func(ans);
			if (fnew == 0.0) return ans;
			if (SIGN(fm,fnew) != fm) {
				xl=xm;
				fl=fm;
				xh=ans;
				fh=fnew;
			} else if (SIGN(fl,fnew) != fl) {
				xh=ans;
				fh=fnew;
			} else if (SIGN(fh,fnew) != fh) {
				xl=ans;
				fl=fnew;
			} else throw("never get here.");
			if (abs(xh-xl) <= xacc) return ans;

            std::cout << "Iteration " << j+1 << " xi: " << xl << " yi: " << xh << std::endl;
		}
        return ans;
		
	}
	else {
		if (fl == 0.0) return x1;
		if (fh == 0.0) return x2;
		throw("root must be bracketed in zriddr.");
	}
}



int main() {
    std::cout << "Exercise 2.1\n" << std::endl;

    std::cout << std::fixed << std::setprecision(8);

    std::cout << "f(-1) = " << f(-1.0) << std::endl;
    std::cout << "f(1)  = " << f(1.0) << std::endl;

//======================================================================================

    std::cout << "\nExercise 2.2\n" << std::endl;

    Doub res = riddersMethod(f, -1.0, 1.0, 0, 4);   // Input is funtion, x1, x2, accuracy (set to 0 to not stop it running) and iteration count
    std::cout << "Ridders solution after 4 iterations: " << res << std::endl;

//======================================================================================

    std::cout << "\nExercise 2.3\n" << std::endl;

    res = riddersMethod(f, -1.0, 1.0, 0, 5);
    std::cout << "Ridders solution after 5 iterations: " << res << std::endl;

    return 0;
}