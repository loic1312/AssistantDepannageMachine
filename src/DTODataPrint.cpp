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

void DTODataPrint::SetLoadingBar(std::string strKey, unsigned int uiValue) {
  m_mListLoadingBar[strKey] = uiValue;
}

void DTODataPrint::SetPointGraphic(float fX, float fY) { m_mGraphic[fX] = fY; }

void DTODataPrint::setHeaderTable(std::vector<std::string> vHeaderTable) {
  m_vHeaderTable = vHeaderTable;
}

void DTODataPrint::setDataTable(std::vector<std::vector<std::string>> vDataTable) {
  m_vDataTable = vDataTable;
}

void DTODataPrint::setHeaderLineTable(
    std::vector<std::string> vHeaderLineTable) {
  m_vHeaderLineTable = vHeaderLineTable;
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

std::map<std::string, unsigned int> DTODataPrint::GetLoadingBar() {
  return m_mListLoadingBar;
}

std::map<float, float> DTODataPrint::GetGraphic() { return m_mGraphic; }

std::vector<std::string> DTODataPrint::GetHeaderTable() {
  return m_vHeaderTable;
}

std::vector<std::vector<std::string>> DTODataPrint::GetDataTable() {
  return m_vDataTable;
}

std::vector<std::string> DTODataPrint::GetHeaderLineTable() {
  return m_vHeaderLineTable;
}

void DTODataPrint::ClearHeaderValue() { m_mHeaderValue.clear(); }

void DTODataPrint::ClearArticleValue() { m_mArticleValue.clear(); }

void DTODataPrint::CleartNavValue() { m_mNavValue.clear(); }

void DTODataPrint::ClearFooterValue() { m_mFooterValue.clear(); }

void DTODataPrint::ClearLoadingBar() { m_mListLoadingBar.clear(); }

void DTODataPrint::ClearGraphic() { m_mGraphic.clear(); }
