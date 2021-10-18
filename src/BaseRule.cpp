#include "BaseRule.h"

BaseRule::BaseRule() {}

BaseRule::~BaseRule() {}

void BaseRule::ClearListRule() { m_vListRule.clear(); }

void BaseRule::AddRule(Rule rRule) {
  bool bRuleIsExiste = false;
  for (std::vector<Rule>::iterator it = m_vListRule.begin();
       it != m_vListRule.end(); ++it) {
    if (it->GetName() == rRule.GetName()) {
      bRuleIsExiste = true;
      break;
    }
  }
  if (bRuleIsExiste == false) {
    m_vListRule.push_back(rRule);
  }
}

void BaseRule::RemoveRule(std::string strNameRule) {
  bool bRuleIsExiste = false;
  std::vector<Rule>::iterator itRule;
  for (std::vector<Rule>::iterator it = m_vListRule.begin();
       it != m_vListRule.end(); ++it) {
    if (it->GetName() == strNameRule) {
      bRuleIsExiste = true;
      itRule = it;
      break;
    }
  }
  if (bRuleIsExiste == true) {
    m_vListRule.erase(itRule);
  }
}

std::vector<Rule> BaseRule::GetListRule() { return m_vListRule; }

void BaseRule::SetListRule(std::vector<Rule> vListRule) {
  m_vListRule = vListRule;
}

std::string BaseRule::ToString() {
  std::string strMsg;
  strMsg.append("BaseRule:\n\r");
  for (std::vector<Rule>::iterator it = m_vListRule.begin();
       it != m_vListRule.end(); ++it) {
    strMsg.append(it->ToString());
    strMsg.append("\n\r");
  }
  return strMsg;
}
