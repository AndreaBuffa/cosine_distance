#include <iostream>
#include <math.h>
#include <vector>
#include "UIMatrix.h"

using namespace std;

int main (int argc, char** argv)
{
  const size_t n = 1 * pow(10, 6); // matrix size 1 * 10 ^ 6

  UVector<int> activeUser(0, n);
  activeUser.set(0, 1);
  activeUser.set(2, 1);
  //std::cout << "Active User profile:\n" << activeUser.get(0) << std::endl;

  UIMatrix<UVector<int> > users(0, 0, n);

  users.set(0, 0, 1);
  users.set(0, 2, 1);

  users.set(1, 1, 1);
  users.set(1, 2, 1);

  users.set(2, 0, 1);
  users.set(2, 1, 1);
  users.set(2, 2, 1);

  UVector<vector<int> > res(0, n);
  // retrive a / b * c
  users.getPartialOperands(activeUser, res);

  double cosineDistance = 0.0;
  for(UVector<vector<int> >::v_iter it = res.begin(); it != res.end(); it++) {
    if (it->second[1] != 0 && it->second[2] != 0) {
      //std::cout << "TEST" << it->second[0]  << std::endl;
      // compute cosine(angle) = a / b * c
      cosineDistance = it->second[0] / (sqrt(it->second[1]) * sqrt(it->second[2]));
    } else {
      cosineDistance = 0.0;
    }
    std::cout << "Distance:" << cosineDistance << std::endl;
  }
  return 0;
}
