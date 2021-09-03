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

#include<string>

template <typename T> class Fact {
 private:
    std::string m_strName;
    int m_iLevel;
    std::string m_strIssue;
    T m_Value;
 public:
  Fact(std::string strName, int iLevel, std::string strIssue, T Value);
  ~Fact();

  void SetLevel(int iLevel);

  std::string GetName();
  int GetLevel();
  std::string GetIssue();
  T GetValue();
};

#endif  // HEADER_FACT_H_
