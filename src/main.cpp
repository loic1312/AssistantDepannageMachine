/**
 * @file main.cpp
 * @author PASSARET Loic
 * @brief Lancement de l'assistant de depannage et gestion code de retour
 * @version 0.1
 * @date 2021-09-03
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <iostream>

#include "BaseFact.h"
#include "BaseRule.h"
#include "Fact.h"
#include "Rule.h"
#include "SteamInference.h"

int main(int argc, char const *argv[]) {
  if (argc == 2) {
    std::cout << "Assistant Depannage start" << std::endl;
    SteamInference si;
    si.InitRule(argv[1]);
    si.Solve();
  } else {
    std::cout << "Usage: ./MachineExpertMaxiCoffee /path/rule.xml" << std::endl;
  }

  return 0;
}
