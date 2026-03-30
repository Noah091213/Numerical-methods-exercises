#include <fstream>
#include <string>

using namespace std;

int getFileData(const string& filename, VecDoub& uOut, VecDoub& vOut) {
  // Open file
  const char* f = &filename[0];
  //inFile.open(f);
  ifstream inFile(f);
  // Calculate number of points
  int N(0);
  string xs;
  while(inFile >> xs)
    N++;
  
  inFile.close();
  // Subtract header information
  N -= 3;
  // Use number of pairs
  N /= 2;
  
  // Get data values (u, v)
  VecDoub u(N, 0.0), v(N, 0.0);
  inFile.open(f);
  char* sp = &xs[0];
  // For each data value
  for(int i = 0; i < 2 * N + 3; i++) {
    inFile >> xs;
    if(i > 2) {
      if(i % 2 != 0) // y-values
        v[(int)(i - 3) / 2] = atof(sp);
      else
        u[(int)(i - 3) / 2] = atof(sp);
    }
  }
  inFile.close();
  
  uOut = u;
  vOut = v;
  
  return N;
}
