#include "InterfaceCmd.h"

InterfaceCmd::InterfaceCmd() { m_bScanKeyboard = false; }

InterfaceCmd::~InterfaceCmd() {}

void InterfaceCmd::PrintScreen(DTODataPrint DataPrint) {
  m_DataPrint = DataPrint;
  std::lock_guard<std::mutex> lock(m_mtxDisplay);
  m_strEcran.clear();
  InsertValueInMsg();
  PrintHeader();
  PrintSeparator();
  PrintNav();
  PrintSeparator();
  PrintArticle();
  if (m_bPrintGraphic) {
    PrintGraphic();
  }
  if (m_bLoadingBarActivate) {
    PrintLoadingBar();
  }
  PrintSeparator();
  PrintFooter();
  PrintSeparator();
  std::system("clear");
  std::cout << m_strEcran << std::endl;
  if (m_bLoadingActivate) {
    m_tPrintMenuLoading =
        std::thread(std::bind(&InterfaceCmd::PrintMenuLoading, this));
  }
}

void InterfaceCmd::PrintMenuLoading() {
  unsigned int uiLengthBar = m_uiWidthMax / 10;
  unsigned int uiStartBar = 0;
  bool bIsRigth = true;
  std::string strBar;
  for (unsigned int i = uiStartBar; i < uiLengthBar; ++i) {
    strBar.append("=");
  }
  while (m_bLoadingActivate) {
    std::lock_guard<std::mutex> lock(m_mtxDisplay);
    m_strEcran.clear();
    InsertValueInMsg();
    PrintHeader();
    PrintSeparator();
    PrintNav();
    PrintSeparator();
    PrintArticle();
    m_strEcran.append("|");
    unsigned int uiLimit = uiStartBar + uiLengthBar;
    if (uiLimit >= m_uiWidthMax - 1) {
      uiLimit = m_uiWidthMax;
      bIsRigth = false;
      uiStartBar = m_uiWidthMax - uiLengthBar - 2;
    }
    if (uiStartBar == 0) {
      bIsRigth = true;
    }
    for (unsigned int i = 0; i < uiStartBar; ++i) {
      m_strEcran.append("-");
    }
    m_strEcran.append(strBar);
    for (unsigned int i = uiLimit; i < m_uiWidthMax - 2; ++i) {
      m_strEcran.append("-");
    }
    m_strEcran.append("|");
    m_strEcran.append("\n\r");
    PrintSeparator();
    PrintFooter();
    PrintSeparator();
    std::system("clear");
    std::cout << m_strEcran << std::endl;
    if (bIsRigth) {
      uiStartBar += 1;
    } else {
      uiStartBar -= 1;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }
}

void InterfaceCmd::StartScanKeyboard() {
  m_thScanKeyboard = std::thread(std::bind(&InterfaceCmd::KeyboardInput, this));
}

void InterfaceCmd::StopScanKeyboard() { m_thScanKeyboard.join(); }

void InterfaceCmd::KeyboardInput() {
  std::chrono::seconds span(1);
  std::future<std::string> future =
      std::async(std::bind(&InterfaceCmd::ScanInputValueKeyboard, this));
  while (SafeGetValueScanKeyboard()) {
    if (future.wait_for(span) == std::future_status::ready) {
      std::string data = future.get();
      m_callbackKeyboardInput(data);
      if (data == m_strKeyStop) {
        setScanKeyboard(false);
      } else {
        future =
            std::async(std::bind(&InterfaceCmd::ScanInputValueKeyboard, this));
      }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}

std::string InterfaceCmd::ScanInputValueKeyboard() {
  std::string value;
  std::cin >> value;
  return value;
}

void InterfaceCmd::setCallbackKeyboardInput(
    std::function<void(std::string)> callback) {
  m_callbackKeyboardInput = callback;
}

void InterfaceCmd::setScanKeyboard(bool bScan) {
  std::lock_guard<std::mutex> lock(m_mtxScanKeyboard);
  m_bScanKeyboard = bScan;
}

void InterfaceCmd::setWidthMax(unsigned int uiWidthMax) {
  m_uiWidthMax = uiWidthMax;
}

void InterfaceCmd::setBbrNav(unsigned int uiBbrNav) { m_uiBbrNav = uiBbrNav; }

void InterfaceCmd::setKeyStop(std::string strKeyStop) {
  m_strKeyStop = strKeyStop;
}

void InterfaceCmd::setKeyValueStart(std::string strKeyValueStart) {
  m_strKeyValueStart = strKeyValueStart;
}

void InterfaceCmd::setKeyValueStop(std::string strKeyValueStop) {
  m_strKeyValueStop = strKeyValueStop;
}

void InterfaceCmd::setLoadingBarActivate(bool bLoadingBarActivate) {
  m_bLoadingBarActivate = bLoadingBarActivate;
}

void InterfaceCmd::setLoadingActivate(bool bLoadingActivate) {
  m_bLoadingActivate = bLoadingActivate;
  if (bLoadingActivate == false) {
    m_tPrintMenuLoading.join();
  }
}

void InterfaceCmd::setPrintGraphic(bool bPrintGraphic) {
  m_bPrintGraphic = bPrintGraphic;
}

void InterfaceCmd::setHeigthGraph(unsigned int uiHeigth) {
  m_uiHeigthGraph = uiHeigth;
}

bool InterfaceCmd::SafeGetValueScanKeyboard() {
  std::lock_guard<std::mutex> lock(m_mtxScanKeyboard);
  return m_bScanKeyboard;
}

void InterfaceCmd::InsertValueInMsg() {
  m_vHeader = m_DataPrint.GetHeader();
  m_vArticle = m_DataPrint.GetArticle();
  m_vNav = m_DataPrint.GetNav();
  m_vFooter = m_DataPrint.GetFooter();
  for (std::vector<std::string>::iterator it = m_vHeader.begin();
       it != m_vHeader.end(); ++it) {
    while (it->find(m_strKeyValueStart) != std::string::npos) {
      std::size_t firstFound = it->find(m_strKeyValueStart);
      std::size_t lastFound = it->find(m_strKeyValueStop);
      std::string keyValue =
          it->substr(firstFound + 2, lastFound - firstFound - 2);
      it->replace(firstFound, lastFound - firstFound + 2,
                  m_DataPrint.GetHeaderValue()[keyValue]);
    }
  }
  for (std::vector<std::string>::iterator it = m_vArticle.begin();
       it != m_vArticle.end(); ++it) {
    while (it->find(m_strKeyValueStart) != std::string::npos) {
      std::size_t firstFound = it->find(m_strKeyValueStart);
      std::size_t lastFound = it->find(m_strKeyValueStop);
      std::string keyValue =
          it->substr(firstFound + 2, lastFound - firstFound - 2);
      it->replace(firstFound, lastFound - firstFound + 2,
                  m_DataPrint.GetArticleValue()[keyValue]);
    }
  }
  for (std::vector<std::string>::iterator it = m_vNav.begin();
       it != m_vNav.end(); ++it) {
    while (it->find(m_strKeyValueStart) != std::string::npos) {
      std::size_t firstFound = it->find(m_strKeyValueStart);
      std::size_t lastFound = it->find(m_strKeyValueStop);
      std::string keyValue =
          it->substr(firstFound + 2, lastFound - firstFound - 2);
      it->replace(firstFound, lastFound - firstFound + 2,
                  m_DataPrint.GetNavValue()[keyValue]);
    }
  }
  for (std::vector<std::string>::iterator it = m_vFooter.begin();
       it != m_vFooter.end(); ++it) {
    while (it->find(m_strKeyValueStart) != std::string::npos) {
      std::size_t firstFound = it->find(m_strKeyValueStart);
      std::size_t lastFound = it->find(m_strKeyValueStop);
      std::string keyValue =
          it->substr(firstFound + 2, lastFound - firstFound - 2);
      it->replace(firstFound, lastFound - firstFound + 2,
                  m_DataPrint.GetFooterValue()[keyValue]);
    }
  }
}

std::string InterfaceCmd::FloatToString(float fValue,
                                        unsigned int uiPrecision) {
  std::stringstream stream;
  stream << std::fixed << std::setprecision(uiPrecision) << fValue;
  return stream.str();
}

void InterfaceCmd::PrintHeader() {
  for (std::vector<std::string>::iterator it = m_vHeader.begin();
       it != m_vHeader.end(); ++it) {
    if (it->size() < m_uiWidthMax) {
      m_strEcran.append(*it);
      m_strEcran.append("\n\r");
    } else {
      unsigned int uiIndexStr = 0;
      while (uiIndexStr < it->size()) {
        m_strEcran.append(it->substr(uiIndexStr, m_uiWidthMax));
        uiIndexStr = uiIndexStr + m_uiWidthMax;
        m_strEcran.append("\n\r");
      }
    }
  }
}

void InterfaceCmd::PrintNav() {
  unsigned int uiLengthMaxNav = floor(m_uiWidthMax / m_uiBbrNav) - 1;
  unsigned int uiCounterNav = 0;
  for (std::vector<std::string>::iterator it = m_vNav.begin();
       it != m_vNav.end(); ++it) {
    if (uiCounterNav >= m_uiBbrNav) {
      m_strEcran.append("\n\r");
      uiCounterNav = 0;
    }
    unsigned int uiLengthNav = it->size();
    if (uiLengthNav < uiLengthMaxNav) {
      m_strEcran.append(*it);
      for (unsigned int i = 0; i < (uiLengthMaxNav - uiLengthNav); ++i) {
        m_strEcran.append(" ");
      }
    } else {
      std::string strSubNav = it->substr(0, uiLengthMaxNav);
      m_strEcran.append(strSubNav);
    }
    m_strEcran.append("|");
    uiCounterNav += 1;
    if (it == m_vNav.end() - 1) {
      m_strEcran.append("\n\r");
    }
  }
}

void InterfaceCmd::PrintArticle() {
  for (std::vector<std::string>::iterator it = m_vArticle.begin();
       it != m_vArticle.end(); ++it) {
    if (it->size() < m_uiWidthMax) {
      m_strEcran.append(*it);
      m_strEcran.append("\n\r");
    } else {
      unsigned int uiIndexStr = 0;
      while (uiIndexStr < it->size()) {
        m_strEcran.append(it->substr(uiIndexStr, m_uiWidthMax));
        uiIndexStr = uiIndexStr + m_uiWidthMax;
        m_strEcran.append("\n\r");
      }
    }
  }
}

void InterfaceCmd::PrintLoadingBar() {
  std::map<std::string, unsigned int> mListBar = m_DataPrint.GetLoadingBar();
  for (std::map<std::string, unsigned int>::iterator it = mListBar.begin();
       it != mListBar.end(); ++it) {
    m_strEcran.append(it->first);
    m_strEcran.append("\n\r");
    unsigned int uivalue = it->second;
    if (uivalue >= 100) {
      uivalue = 99;
    }
    unsigned int uiNbrLoad;
    unsigned int uiFilling;
    m_strEcran.append("|");
    if (uivalue <= 0) {
      uiFilling = m_uiWidthMax - 2;
      uiNbrLoad = 0;
    } else if (uivalue >= 99) {
      uiFilling = 0;
      uiNbrLoad = m_uiWidthMax - 2;
    } else {
      uiNbrLoad = (uivalue * m_uiWidthMax - 2) / 100;
      uiFilling = m_uiWidthMax - uiNbrLoad - 2;
    }
    for (unsigned int i = 0; i < uiNbrLoad; ++i) {
      m_strEcran.append("=");
    }
    for (unsigned int i = 0; i < uiFilling; ++i) {
      m_strEcran.append("-");
    }
    m_strEcran.append("|");
    m_strEcran.append("\n\r");
  }
}

void InterfaceCmd::PrintGraphic() {
  std::map<float, float> mGraphic = m_DataPrint.GetGraphic();
  float fXMin = mGraphic.begin()->first;
  float fXMax = mGraphic.begin()->first;
  float fYMin = mGraphic.begin()->second;
  float fYMax = mGraphic.begin()->second;
  for (std::map<float, float>::iterator it = mGraphic.begin();
       it != mGraphic.end(); ++it) {
    if (it->first < fXMin) {
      fXMin = it->first;
    }
    if (it->first > fXMax) {
      fXMax = it->first;
    }
    if (it->second < fYMin) {
      fYMin = it->second;
    }
    if (it->second > fYMax) {
      fYMax = it->second;
    }
  }
  std::vector<std::string> vGraph;
  for (unsigned int y = 0; y < m_uiHeigthGraph; ++y) {
    std::string strLine;
    for (unsigned int x = 0; x < m_uiWidthMax; ++x) {
      strLine.append(" ");
    }
    vGraph.push_back(strLine);
  }
  unsigned uiXZero = (m_uiWidthMax - 1) * ((0 - fXMin) / (fXMax - fXMin));
  unsigned uiYZero = (m_uiHeigthGraph - 1) * ((0 - fYMin) / (fYMax - fYMin));
  for (std::vector<std::string>::iterator it = vGraph.begin();
       it != vGraph.end(); ++it) {
    it->insert(uiXZero, "#");
    it->pop_back();
  }
  vGraph[uiYZero].clear();
  for (unsigned int i = 0; i < m_uiWidthMax; ++i) {
    vGraph[uiYZero].append("#");
  }
  for (std::map<float, float>::iterator it = mGraphic.begin();
       it != mGraphic.end(); ++it) {
    float fXScale = (it->first - fXMin) / (fXMax - fXMin);
    float fYScale = (it->second - fYMin) / (fYMax - fYMin);
    unsigned int uiX = (m_uiWidthMax - 1) * fXScale;
    unsigned int uiY = (m_uiHeigthGraph - 1) * fYScale;
    vGraph[uiY][uiX] = 'x';
  }
  for (std::vector<std::string>::iterator it = vGraph.end() - 1;
       it != vGraph.begin(); --it) {
    m_strEcran.append(*it);
    m_strEcran.append("\n\r");
  }
  m_strEcran.append(vGraph[0]);
  m_strEcran.append("\n\r");
}

void InterfaceCmd::PrintFooter() {
  for (std::vector<std::string>::iterator it = m_vFooter.begin();
       it != m_vFooter.end(); ++it) {
    if (it->size() < m_uiWidthMax) {
      m_strEcran.append(*it);
      m_strEcran.append("\n\r");
    } else {
      unsigned int uiIndexStr = 0;
      while (uiIndexStr < it->size()) {
        m_strEcran.append(it->substr(uiIndexStr, m_uiWidthMax));
        uiIndexStr = uiIndexStr + m_uiWidthMax;
        m_strEcran.append("\n\r");
      }
    }
  }
}

void InterfaceCmd::PrintSeparator() {
  std::string strSeparator;
  for (unsigned int i = 1; i <= m_uiWidthMax; ++i) {
    strSeparator.append("#");
  }
  strSeparator.append("\n\r");
  m_strEcran.append(strSeparator);
}
