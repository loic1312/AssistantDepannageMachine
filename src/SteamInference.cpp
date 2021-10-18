#include "SteamInference.h"

int SteamInference::IsRevelant(Rule rRule) {
  int iLevelMax = -1;
  for (std::vector<Fact>::iterator it = rRule.GetPremisse().begin();
       it != rRule.GetPremisse().end(); ++it) {
    Fact fFactFind = m_BaseFact.GetFact(it->GetName());
    if (fFactFind.GetName() == "NONE") {
      if (it->GetIssue() != "NONE") {
        std::string strValue = m_IHMCmd.GetData(it->GetIssue());
        m_BaseFact.AddFact(
            Fact(it->GetName(), 0, it->GetIssue(), strValue, it->GetType()));
        fFactFind =
            Fact(it->GetName(), 0, it->GetIssue(), strValue, it->GetType());
      } else {
        return -1;
      }
    }
    if (it->GetValue() != fFactFind.GetValue()) {
      return -1;
    } else {
      if (iLevelMax <= fFactFind.GetLevel()) {
        iLevelMax = fFactFind.GetLevel();
      }
    }
  }
  return iLevelMax;
}

Rule SteamInference::FindRule() {
  for (std::vector<Rule>::iterator it = m_BaseRule.GetListRule().begin();
       it != m_BaseRule.GetListRule().end(); ++it) {
    int iLevel = IsRevelant(*it);
    if (iLevel != -1) {
      m_iLevelMax = iLevel;
      return *it;
    }
  }
}

SteamInference::SteamInference() {}

SteamInference::~SteamInference() {}

void SteamInference::InitRule(std::string strPathFileConfig) {
  m_IHMCmd.Display("Init Rules...");
  DriverXml xml(strPathFileConfig);
  boost::property_tree::ptree xmltree = xml.LoadXml();
  BOOST_FOREACH (boost::property_tree::ptree::value_type &rules,
                 xmltree.get_child("Rules")) {
    boost::property_tree::ptree rule = rules.second;
    Rule r;
    std::vector<Fact> fPremisses;
    r.SetName(rule.get<std::string>("Name"));
    BOOST_FOREACH (boost::property_tree::ptree::value_type &premisses,
                   rule.get_child("Premisses")) {
      boost::property_tree::ptree premisse = premisses.second;
      Fact f(premisse.get<std::string>("Name"), 0,
             premisse.get<std::string>("Issue"),
             premisse.get<std::string>("Value"),
             premisse.get<std::string>("Type"));
      fPremisses.push_back(f);
    }
    r.SetPremisse(fPremisses);
    boost::property_tree::ptree pConclusion = rule.get_child("Conclusion");
    Fact fConclusion(pConclusion.get<std::string>("Name"), 0,
                     pConclusion.get<std::string>("Issue"),
                     pConclusion.get<std::string>("Value"),
                     pConclusion.get<std::string>("Type"));
    r.SetConclusion(fConclusion);
    m_BaseRule.AddRule(r);
  }
  m_IHMCmd.Display(ToString());
}

void SteamInference::Solve() {
  std::string strAnswer;
  strAnswer = m_IHMCmd.GetData("Start solve? yes/no");
  if (strAnswer == "yes") {
    m_IHMCmd.Display("Solving...");
    Rule rRule;
    rRule.SetName("NONE");
    rRule = FindRule();
    while (rRule.GetName() != "NONE") {
      Fact fFact = rRule.GetConclusion();
      fFact.SetLevel(m_iLevelMax + 1);
      m_BaseFact.AddFact(fFact);
      m_BaseRule.RemoveRule(rRule.GetName());
      rRule.SetName("NONE");
      rRule = FindRule();
    }
    m_IHMCmd.Display(m_BaseFact.ToString());
  } else {
    m_IHMCmd.Display("Exit");
  }
}

std::string SteamInference::ToString() { return m_BaseRule.ToString(); }
