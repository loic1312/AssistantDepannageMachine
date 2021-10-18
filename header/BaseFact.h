/**
 * @file BaseFact.h
 * @author PASSARET Loïc
 * @brief Sauvegarde tous les faits
 * @version 0.1
 * @date 2021-10-13
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef HEADER_BASEFACT_H_
#define HEADER_BASEFACT_H_

#include <vector>
#include <string>

#include "Fact.h"

class BaseFact {
 private:
  std::vector<Fact> m_vListFact;

 public:
  BaseFact();
  ~BaseFact();

  bool AddFact(Fact fFact);
  std::vector<Fact> GetListFact();
  void ClearListFact();
  Fact GetFact(std::string strNameFact);
  std::string GetValueFact(std::string strNameFact);
  std::string ToString();
};

#endif  // HEADER_BASEFACT_H_
