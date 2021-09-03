#include "Fact.h"

Fact::Fact(std::string strName, int iLevel, std::string strIssue, T Value) {
  m_strName = strName;
  m_iLevel = iLevel;
  m_strIssue = strIssue;
  m_Value = Value;
}

Fact::~Fact() {}

void Fact::SetLevel(int iLevel) { m_iLevel = iLevel; }

std::string Fact::GetName() { return m_strName; }

int Fact::GetLevel() { return m_iLevel; }

std::string Fact::GetIssue() { return m_strIssue; }

T Fact::GetValue() { return m_Value; }
