#include "SteamInference.h"

SteamInference::SteamInference() {}

SteamInference::~SteamInference() {}

void SteamInference::InitRule(std::string strPathFileConfig) {
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
}

void SteamInference::Solve() {}

std::string SteamInference::ToString() { return m_BaseRule.ToString(); }
