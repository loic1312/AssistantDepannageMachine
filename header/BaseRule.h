/**
 * @file BaseRule.h
 * @author PASSARET Loïc
 * @brief Sauvegarde les régles
 * @version 0.1
 * @date 2021-10-15
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef HEADER_BASERULE_H_
#define HEADER_BASERULE_H_

#include <vector>

#include "Rule.h"

class BaseRule {
 private:
  std::vector<Rule> m_vListRule;

 public:
  BaseRule();
  ~BaseRule();

  void ClearListRule();
  void AddRule(Rule rRule);
  void RemoveRule(std::string strNameRule);

  std::vector<Rule> GetListRule();

  void SetListRule(std::vector<Rule> vListRule);

  std::string ToString();
};

#endif  // HEADER_BASERULE_H_
