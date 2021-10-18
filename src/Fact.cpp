#include "Fact.h"

Fact::Fact() {}

Fact::Fact(std::string strName, int iLevel, std::string strIssue,
           std::string strValue, std::string strType) {
  m_strValue = strValue;
  m_strName = strName;
  m_iLevel = iLevel;
  m_strIssue = strIssue;
  m_strType = strType;
}

Fact::~Fact() {}

std::string Fact::GetValue() { return m_strValue; }

std::string Fact::GetName() { return m_strName; }

int Fact::GetLevel() { return m_iLevel; }

std::string Fact::GetIssue() { return m_strIssue; }

std::string Fact::GetType() { return m_strType; }

void Fact::SetLevel(int iLevel) { m_iLevel = iLevel; }

std::string Fact::ToString() {
  std::string strMsg;
  strMsg.append("Fact: ");
  strMsg.append("Name: ");
  strMsg.append(GetName());
  strMsg.append(" Level: ");
  strMsg.append(std::to_string(GetLevel()));
  strMsg.append(" Type: ");
  strMsg.append(GetType());
  strMsg.append(" Issue: ");
  strMsg.append(GetIssue());
  strMsg.append(" Value: ");
  strMsg.append(GetValue());
  return strMsg;
}
