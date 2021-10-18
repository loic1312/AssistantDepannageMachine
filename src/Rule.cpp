#include "Rule.h"

Rule::Rule() {}

Rule::~Rule() {}

void Rule::SetName(std::string strName) { m_strName = strName; }

void Rule::SetConclusion(Fact fConclusion) { m_FactOutput = fConclusion; }

void Rule::SetPremisse(std::vector<Fact> vPremisse) {
  m_vFactIntput = vPremisse;
}

std::string Rule::GetName() { return m_strName; }

Fact Rule::GetConclusion() { return m_FactOutput; }

std::vector<Fact> Rule::GetPremisse() { return m_vFactIntput; }

std::string Rule::ToString() {
  std::string strMsg;
  strMsg.append("Rule: ");
  strMsg.append("Name: ");
  strMsg.append(GetName());
  strMsg.append(" IF ( ");
  for (std::vector<Fact>::iterator it = m_vFactIntput.begin();
       it != m_vFactIntput.end(); ++it) {
    strMsg.append(it->ToString());
    strMsg.append("/");
  }
  strMsg.append(" ) THEN ");
  strMsg.append(m_FactOutput.ToString());
  return strMsg;
}
