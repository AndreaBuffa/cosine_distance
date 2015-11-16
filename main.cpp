#include <iostream>
#include <math.h>
#include "UIMatrix.h"

int main ()
{
  UVector<int> activeUser(0, 10);
  activeUser.set(0, 1);
  //activeUser.set(3, 1);
  std::cout << "Active User profile:\n" << activeUser.get(0) << std::endl;

  UIMatrix users(0, 0, 10);
  users.set(0, 0, 1);
  //users.set(0, 3, 1);
  users.set(1, 1, 1);

  //int res[3] = {0, 0, 0};
  UVector<int*> res(0, 10);
  users.dotProduct(activeUser, res);

  double cosineDistance = 0.0;
  for(UVector<int*>::iterator it = res.begin(); it != res.end(); it++) {
    if (it->second[1] != 0 && it->second[2] != 0) {
      //std::cout << "TEST" << it->first << std::endl;
      cosineDistance = (double)it->second[0] / sqrt((double)(it->second[1]) * sqrt((double)it->second[2]));
    } else {
      cosineDistance = 0.0;
    }
    delete[] it->second;
    std::cout << "Distance:" << cosineDistance << std::endl;
  }
  return 0;
}
