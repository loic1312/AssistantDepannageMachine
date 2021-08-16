#include "DTODataPrint.h"

DTODataPrint::DTODataPrint() {}

DTODataPrint::~DTODataPrint() {}

void DTODataPrint::SetHeader(std::vector<std::string> vHeader) {
  m_vHeader = vHeader;
}

void DTODataPrint::SetArticle(std::vector<std::string> vArticle) {
  m_vArticle = vArticle;
}

void DTODataPrint::SetNav(std::vector<std::string> vNav) { m_vNav = vNav; }

void DTODataPrint::SetFooter(std::vector<std::string> vFooter) {
  m_vFooter = vFooter;
}

std::vector<std::string> DTODataPrint::GetHeader() { return m_vHeader; }

std::vector<std::string> DTODataPrint::GetArticle() { return m_vArticle; }

std::vector<std::string> DTODataPrint::GetNav() { return m_vNav; }

std::vector<std::string> DTODataPrint::GetFooter() { return m_vFooter; }

void DTODataPrint::ClearHeader() { m_vHeader.clear(); }

void DTODataPrint::ClearArticle() { m_vArticle.clear(); }

void DTODataPrint::CleartNav() { m_vNav.clear(); }

void DTODataPrint::ClearFooter() { m_vFooter.clear(); }

void DTODataPrint::SetHeaderValue(std::string strKey, std::string strValue) {
  m_mHeaderValue[strKey] = strValue;
}

void DTODataPrint::SetArticleValue(std::string strKey, std::string strValue) {
  m_mArticleValue[strKey] = strValue;
}

void DTODataPrint::SetNavValue(std::string strKey, std::string strValue) {
  m_mNavValue[strKey] = strValue;
}

void DTODataPrint::SetFooterValue(std::string strKey, std::string strValue) {
  m_mFooterValue[strKey] = strValue;
}

std::map<std::string, std::string> DTODataPrint::GetHeaderValue() {
  return m_mHeaderValue;
}

std::map<std::string, std::string> DTODataPrint::GetArticleValue() {
  return m_mArticleValue;
}

std::map<std::string, std::string> DTODataPrint::GetNavValue() {
  return m_mNavValue;
}

std::map<std::string, std::string> DTODataPrint::GetFooterValue() {
  return m_mFooterValue;
}

void DTODataPrint::ClearHeaderValue() { m_mHeaderValue.clear(); }

void DTODataPrint::ClearArticleValue() { m_mArticleValue.clear(); }

void DTODataPrint::CleartNavValue() { m_mNavValue.clear(); }

void DTODataPrint::ClearFooterValue() { m_mFooterValue.clear(); }
