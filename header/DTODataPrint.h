/**
 * @file DTODataPrint.h
 * @author passaret loic
 * @brief porte les données a afficher dans l'interface
 * @version 0.1
 * @date 2021-07-26
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef HEADER_DTODATAPRINT_H_
#define HEADER_DTODATAPRINT_H_

#include <map>
#include <string>
#include <vector>

class DTODataPrint {
 private:
  std::vector<std::string> m_vHeader;
  std::map<std::string, std::string> m_mHeaderValue;

  std::vector<std::string> m_vArticle;
  std::map<std::string, std::string> m_mArticleValue;

  std::vector<std::string> m_vNav;
  std::map<std::string, std::string> m_mNavValue;

  std::vector<std::string> m_vFooter;
  std::map<std::string, std::string> m_mFooterValue;

  std::map<std::string, unsigned int> m_mListLoadingBar;

  std::map<float, float> m_mGraphic;

 public:
  DTODataPrint();
  ~DTODataPrint();

  void SetHeader(std::vector<std::string> vHeader);
  void SetArticle(std::vector<std::string> vArticle);
  void SetNav(std::vector<std::string> vNav);
  void SetFooter(std::vector<std::string> vFooter);

  std::vector<std::string> GetHeader();
  std::vector<std::string> GetArticle();
  std::vector<std::string> GetNav();
  std::vector<std::string> GetFooter();

  void ClearHeader();
  void ClearArticle();
  void CleartNav();
  void ClearFooter();

  void SetHeaderValue(std::string strKey, std::string strValue);
  void SetArticleValue(std::string strKey, std::string strValue);
  void SetNavValue(std::string strKey, std::string strValue);
  void SetFooterValue(std::string strKey, std::string strValue);
  void SetLoadingBar(std::string strKey, unsigned int uiValue);
  void SetPointGraphic(float fX, float fY);

  std::map<std::string, std::string> GetHeaderValue();
  std::map<std::string, std::string> GetArticleValue();
  std::map<std::string, std::string> GetNavValue();
  std::map<std::string, std::string> GetFooterValue();
  std::map<std::string, unsigned int> GetLoadingBar();
  std::map<float, float> GetGraphic();

  void ClearHeaderValue();
  void ClearArticleValue();
  void CleartNavValue();
  void ClearFooterValue();
  void ClearLoadingBar();
  void ClearGraphic();
};

#endif  // HEADER_DTODATAPRINT_H_
