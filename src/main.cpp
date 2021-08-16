#include <iostream>
#include <unistd.h>

#include "InterfaceCmd.h"
bool bRun = true;
void callback(std::string data) {
  if (data == "STOP") {
    bRun = false;
  } else {
    std::cout << data << std::endl;
  }
}

int main(int argc, char const *argv[]) {
  InterfaceCmd ic;
  ic.setCallbackKeyboardInput(std::bind(callback, std::placeholders::_1));
  ic.setScanKeyboard(true);
  ic.StartScanKeyboard();
  while (bRun) {
  }
  sleep(1);
  ic.setScanKeyboard(false);
  ic.StopScanKeyboard();
  return 0;
}
