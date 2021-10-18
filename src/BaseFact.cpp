#include "BaseFact.h"

BaseFact::BaseFact() {}

BaseFact::~BaseFact() {}

bool BaseFact::AddFact(Fact fFact) { m_vListFact.push_back(fFact); }

std::vector<Fact> BaseFact::GetListFact() { return m_vListFact; }

void BaseFact::ClearListFact() { m_vListFact.clear(); }

Fact BaseFact::GetFact(std::string strNameFact) {
  for (std::vector<Fact>::iterator it = m_vListFact.begin();
       it != m_vListFact.end(); ++it) {
    if (it->GetName() == strNameFact) {
      return *it;
    }
  }
}

std::string BaseFact::GetValueFact(std::string strNameFact) {
  for (std::vector<Fact>::iterator it = m_vListFact.begin();
       it != m_vListFact.end(); ++it) {
    if (it->GetName() == strNameFact) {
      return it->GetValue();
    }
  }
}

std::string BaseFact::ToString() {
  std::string strMsg;
  strMsg.append("BaseFact:\r\n");
  for (std::vector<Fact>::iterator it = m_vListFact.begin();
       it != m_vListFact.end(); ++it) {
    strMsg.append(it->ToString());
    strMsg.append("\n\r");
  }
  return strMsg;
}
