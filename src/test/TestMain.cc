#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <iostream>

int main(int argc, char** argv) {
  std::cout << "Start testing..." << std::endl;

  testing::InitGoogleMock(&argc, argv);

  return RUN_ALL_TESTS();
}

