/**
 * @file Rule.h
 * @author PASSARET Loïc
 * @brief Gestion des données d'une regle
 * @version 0.1
 * @date 2021-10-15
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef HEADER_RULE_H_
#define HEADER_RULE_H_

#include <string>
#include <vector>

#include "Fact.h"

class Rule {
 private:
  std::string m_strName;
  std::vector<Fact> m_vFactIntput;
  Fact m_FactOutput;

 public:
  Rule();
  ~Rule();

  void SetName(std::string strName);
  void SetConclusion(Fact fConclusion);
  void SetPremisse(std::vector<Fact> vPremisse);

  std::string GetName();
  Fact GetConclusion();
  std::vector<Fact> GetPremisse();

  std::string ToString();
};

#endif  // HEADER_RULE_H_
