#include "InterfaceCmd.h"

InterfaceCmd::InterfaceCmd() { m_bScanKeyboard = false; }

InterfaceCmd::~InterfaceCmd() {}

void InterfaceCmd::PrintScreen(DTODataPrint DataPrint) {
  m_DataPrint = DataPrint;
  std::lock_guard<std::mutex> lock(m_mtxDisplay);
  std::system("clear");
  m_strEcran.clear();
  InsertValueInMsg();
  PrintHeader();
  PrintArticleNav();
  PrintFooter();
  std::cout << m_strEcran << std::endl;
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
      if (data == "STOP") {
        setScanKeyboard(false);
      } else {
        future =
            std::async(std::bind(&InterfaceCmd::ScanInputValueKeyboard, this));
      }
    }
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

void InterfaceCmd::setWidthNavMax(unsigned int uiWidthMax) {
  m_uiWidthNavMax = uiWidthMax;
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
    while (it->find("<!") != std::string::npos) {
      std::size_t firstFound = it->find_first_of("<!");
      std::size_t lastFound = it->find_first_of("!>");
      std::string keyValue = it->substr(firstFound + 2, lastFound - 2);
      it->replace(firstFound, lastFound - firstFound,
                  m_DataPrint.GetHeaderValue()[keyValue]);
    }
  }
}

void InterfaceCmd::PrintHeader() {
  for (std::vector<std::string>::iterator it = m_vHeader.begin();
       it != m_vHeader.end(); ++it) {
    if (it->size() < m_uiWidthMax) {
      m_strEcran.append(*it);
      m_strEcran.append("\n\r");
    } else {
      m_strEcran.append(*it);
      m_strEcran.append("\n\r");
    }
  }
}

void InterfaceCmd::PrintArticleNav() {
  unsigned int uiIndexMaxNav = m_vNav.size();
  unsigned int uiIndexMaxArticle = m_vArticle.size();
  unsigned int uiIndex = 0;
  unsigned int uiIndexMax;
  unsigned int uiMaxLengthNav = 0;
  if (uiIndexMaxNav < uiIndexMaxArticle) {
    uiIndexMax = uiIndexMaxArticle;
  } else {
    uiIndexMax = uiIndexMaxNav;
  }
  for (uiIndex = 0; uiIndex < uiIndexMax; ++uiIndex) {
    if (uiIndex < uiIndexMaxNav) {
      if (uiMaxLengthNav < m_vNav[uiIndex].size()) {
        uiMaxLengthNav = m_vNav[uiIndex].size();
      }
      if (m_vNav[uiIndex].size() < m_uiWidthNavMax) {
        m_strEcran.append(m_vNav[uiIndex]);
      } else {
      }

    } else {
      for (unsigned int i = 0; i < uiMaxLengthNav; ++i) {
        m_strEcran.append(" ");
      }
    }
    m_strEcran.append(" # ");
    if (uiIndex < uiIndexMaxArticle) {
    } else {
    }
  }
}

void InterfaceCmd::PrintFooter() {
  for (std::vector<std::string>::iterator it = m_vFooter.begin();
       it != m_vFooter.end(); ++it) {
    m_strEcran.append(*it);
    m_strEcran.append("\n\r");
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
