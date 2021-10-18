#include "DriverXml.h"

DriverXml::DriverXml(std::string strPathXml) {
  m_strPathXml = strPathXml;
}
DriverXml::~DriverXml() {}

void DriverXml::setPathXsd(std::string strPathXsd) {
  m_strPathXsd = strPathXsd;
}
bool DriverXml::ValidateXml() { return true; }

boost::property_tree::ptree DriverXml::LoadXml() {
  if (m_strPathXml.empty()) {
    std::cout << "Error path xml empty" << std::endl;
  } else {
    if (boost::filesystem::exists(m_strPathXml)) {
      try {
        boost::property_tree::xml_parser::read_xml(m_strPathXml, m_ConfigTree);
        return m_ConfigTree;
      } catch (const std::exception &e) {
        std::string strMsgError;
        strMsgError.append("Error read config file xml: ");
        strMsgError.append(e.what());
        std::cout << strMsgError << std::endl;
      }
    } else {
      std::cout << "Config file not found" << std::endl;
    }
  }
}
