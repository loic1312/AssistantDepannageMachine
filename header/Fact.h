/**
 * @file Fact.h
 * @author Passaret Loic
 * @brief Class qui sauvegarde les données d'un fait
 * @version 0.1
 * @date 2021-09-03
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef HEADER_FACT_H_
#define HEADER_FACT_H_

#include <string>

class Fact {
 private:
  std::string m_strValue;
  std::string m_strName;
  int m_iLevel;
  std::string m_strIssue;
  std::string m_strType;

 public:
  Fact();
  Fact(std::string strName, int iLevel, std::string strIssue,
       std::string strValue, std::string strType);
  ~Fact();

  std::string GetValue();
  std::string GetName();
  int GetLevel();
  std::string GetIssue();
  std::string GetType();

  void SetLevel(int iLevel);

  std::string ToString();
};

#endif  // HEADER_FACT_H_
