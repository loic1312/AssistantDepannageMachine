/**
 * @file InterfaceCmd.h
 * @author passaret loic
 * @brief gestion de l'interface utilisateur en ligne de commande
 * @version 0.1
 * @date 2021-07-23
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef HEADER_INTERFACECMD_H_
#define HEADER_INTERFACECMD_H_

#include <math.h>

#include <chrono>
#include <functional>
#include <future>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include "DTODataPrint.h"

class InterfaceCmd {
 private:
  DTODataPrint m_DataPrint;
  std::mutex m_mtxDisplay;
  std::mutex m_mtxScanKeyboard;
  std::function<void(std::string)> m_callbackKeyboardInput;
  std::thread m_thScanKeyboard;
  bool m_bScanKeyboard;

  unsigned int m_uiWidthMax;
  unsigned int m_uiBbrNav;

  std::string m_strEcran;

  std::vector<std::string> m_vHeader;
  std::vector<std::string> m_vArticle;
  std::vector<std::string> m_vNav;
  std::vector<std::string> m_vFooter;

  std::string m_strKeyStop;
  std::string m_strKeyValueStart;
  std::string m_strKeyValueStop;

  bool m_bLoadingBarActivate;

  bool SafeGetValueScanKeyboard();

  void InsertValueInMsg();

  void PrintHeader();
  void PrintNav();
  void PrintArticle();
  void PrintFooter();
  void PrintSeparator();
  void PrintLoadingBar();

 public:
  InterfaceCmd();
  ~InterfaceCmd();

  void PrintScreen(DTODataPrint DataPrint);
  void KeyboardInput();
  std::string ScanInputValueKeyboard();

  void StartScanKeyboard();
  void StopScanKeyboard();

  void setCallbackKeyboardInput(std::function<void(std::string)> callback);

  void setScanKeyboard(bool bScan);

  void setWidthMax(unsigned int uiWidthMax);
  void setBbrNav(unsigned int uiBbrNav);

  void setKeyStop(std::string strKeyStop);
  void setKeyValueStart(std::string strKeyValueStart);
  void setKeyValueStop(std::string strKeyValueStop);
  void setLoadingBarActivate(bool bLoadingBarActivate);
};

#endif  // HEADER_INTERFACECMD_H_
