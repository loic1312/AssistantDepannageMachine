#ifndef HEADER_STEAMINFERENCE_H_
#define HEADER_STEAMINFERENCE_H_

#include "BaseFact.h"
#include "BaseRule.h"
#include "Fact.h"
#include "Rule.h"
#include "RuleFactory.h"
#include "DriverXml.h"

#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>

class SteamInference {
 private:
  BaseRule m_BaseRule;
  BaseFact m_BaseFact;
  int m_iLevelMax;

 public:
  SteamInference();
  ~SteamInference();

  void InitRule(std::string strPathFileConfig);
  void Solve();

  std::string ToString();
};

#endif  // HEADER_STEAMINFERENCE_H_
