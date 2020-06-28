#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <string>

void debugPrint(std::string str) {
#ifdef DEBUG
  std::cout << str << std::endl;
#endif
}

#endif
