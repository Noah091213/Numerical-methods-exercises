#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include "NR_C301/code/nr3.h"
#include "NR_C301/code/svd.h"

MatDoub loadMatrix(const std::string fileName) {
    std::ifstream fileToRead(fileName);

    // Error check
    if(!fileToRead.is_open()){
        std::cout << "Error during file loading..." << std::endl;
        exit(1);    
    }

    int rows;
    int cols;

    fileToRead >> rows >> cols;

    MatDoub matrix(rows, cols);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            fileToRead >> matrix[i][j];
        }
    }

    fileToRead.close();
    std::cout << "Succesfully loaded file into matrix!" << std::endl;
    return matrix;
}



VecDoub loadVector(const std::string fileName) {
    std::ifstream fileToRead(fileName);

    // Error check
    if(!fileToRead.is_open()){
        std::cout << "Error during file loading..." << std::endl;
        exit(1);    
    }

    int rows;
    int waste; // The .dat file still has a column variable, that is slow

    fileToRead >> rows;
    fileToRead >> waste;

    VecDoub vectorRes(rows);

    for (int i = 0; i < rows; ++i) {
        fileToRead >> vectorRes[i];
    }

    fileToRead.close();
    std::cout << "Succesfully loaded file into vector!" << std::endl;
    return vectorRes;
}



void errorEstimate(SVD inputSVD, double threshold, int assignmentNum) {
    std::cout << "\nPart " << assignmentNum << std::endl;

    for (int i = 0; i < inputSVD.v.nrows(); ++i) {  
        double sumTerm = 0.0;

        for (int j = 0; j < inputSVD.v.ncols(); ++j) {
            if (inputSVD.w[j] > threshold) {
                double term = inputSVD.v[i][j] / inputSVD.w[j];
                sumTerm += pow(term, 2);
            }
        }
        double errorXI = sqrt(sumTerm);

        std::cout << "Error on x[" << i << "] = +/- " << errorXI << std::endl;
    }
}




int main(){
    // Load the .dat files in with the function. One was made for matrices and for vectors
    MatDoub fileA = loadMatrix("../Ex1A.dat");  
    VecDoub fileB = loadVector("../Ex1b.dat");  

    std::cout << "\nExercise 1.1" << std::endl;
    
    SVD fileAsvd(fileA);

    for (int i = 0; i < fileAsvd.w.size(); ++i) {
        std::cout << "W[" << i << "] = " << fileAsvd.w[i] << std::endl;
    }

//======================================================================================

    std::cout << "\nExercise 1.2" << std::endl;

    VecDoub resVectorII(10);
    double thresholdII = 5.32927e-14; // The lowest result is 5.32927e-15, so we are trying something here
    double sumOfErrorII = 0.0;

    fileAsvd.solve(fileB, resVectorII, thresholdII);

    std::cout << "Solution with smallest W removed:" << std::endl;

    for (int i = 0; i < resVectorII.size(); ++i) {
        std::cout << "x[" << i << "] = " << resVectorII[i] << std::endl;
    }

    // find the residual error
    for (int i = 0; i < fileA.nrows(); ++i) {
        double Axi = 0.0; // Reset Axi
        
        for (int j = 0; j < fileA.ncols(); ++j) {
            Axi += fileA[i][j] * resVectorII[j];  
        }

        double differenceII = Axi - fileB[i]; // Subtract the result of Axi with the result from the given data set 

        sumOfErrorII += pow(differenceII, 2);
    }

    double residualErrorII = sqrt(sumOfErrorII);

    std::cout << "The resiudal error ||Ax-b|| = " << residualErrorII << std::endl;

//======================================================================================

    std::cout << "\nExercise 1.3" << std::endl; 

    VecDoub resVectorIII(10);
    double thresholdIII = 9.35182e-08; // The lowest result is 9.35182e-09, so we are trying something here, again
    double sumOfErrorIII = 0.0;

    fileAsvd.solve(fileB, resVectorIII, thresholdIII);

    std::cout << "Solution with 3 smallest W's removed:" << std::endl;

    for (int i = 0; i < resVectorIII.size(); ++i) {
        std::cout << "x[" << i << "] = " << resVectorIII[i] << std::endl;
    }

    // find the residual error
    for (int i = 0; i < fileA.nrows(); ++i) {
        double Axi = 0.0; // Reset Axi
        
        for (int j = 0; j < fileA.ncols(); ++j) {
            Axi += fileA[i][j] * resVectorIII[j];  
        }

        double differenceIII = Axi - fileB[i]; // Subtract the result of Axi with the result from the given data set 

        sumOfErrorIII += pow(differenceIII, 2);
    }

    double residualErrorIII = sqrt(sumOfErrorIII);

    std::cout << "The resiudal error ||Ax-b|| = " << residualErrorIII << std::endl;

//======================================================================================

    std::cout << "\nExercise 1.5" << std::endl; 

    errorEstimate(fileAsvd, thresholdII, 2);   // Part 2
    errorEstimate(fileAsvd, thresholdIII, 3);  // Part 3

//======================================================================================

    std::cout << "\nExercise 1.6" << std::endl;

    for (int j = 0; j < fileAsvd.v.ncols(); ++j) {
        if (fileAsvd.w[j] <= thresholdIII) {
            std::cout << "\nOrthonormal basis vector exluded w[" << j << "] = " << fileAsvd.w[j] << " : " << std::endl;

            for (int i = 0; i < fileAsvd.v.nrows(); ++i){
                std::cout << " v[" << i << "] = " << fileAsvd.v[i][j] << std::endl;
            }
        }
    }
    

    return 0;
}