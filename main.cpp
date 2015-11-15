#include <iostream>
#include "UIMatrix.h"

int main ()
{

  UVector activeUser(0, 10);
  activeUser.set(0, 1);
  std::cout << "Active User profile:\n";

  std::cout << activeUser.get(0) << std::endl;

  UIMatrix users(0, 0, 10);
  //users.set(0, 0, 1);
  users.set(0, 9, 1);

  int res[3] = {0, 0, 0};
  users.dotProduct(activeUser, res);

  float cosineDistance = 0.0;
  if (res[1] != 0 && res[2] != 0) {
    cosineDistance = res[0] / (res[1] * res[2]);
  }
  std::cout << "Distance:" << cosineDistance << std::endl;
  return 0;
}