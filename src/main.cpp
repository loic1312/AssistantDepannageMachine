#include <unistd.h>

#include <iostream>

#include "DTODataPrint.h"
#include "InterfaceCmd.h"

bool bRun = true;
DTODataPrint dp;
InterfaceCmd ic;
void callback(std::string data) {
  if (data == "STOP") {
    bRun = false;
  } else if (data == "Print") {
    ic.PrintScreen(dp);
  } else {
    std::cout << data << std::endl;
  }
}

int main(int argc, char const *argv[]) {
  std::vector<std::string> header;
  header.push_back("Programme de test de l'interface");
  header.push_back("Version: <!version!>");
  dp.SetHeader(header);
  dp.SetHeaderValue("version", "1.0");
  std::vector<std::string> nav;
  nav.push_back("STOP");
  nav.push_back("Print");
  dp.SetNav(nav);
  std::vector<std::string> article;
  article.push_back("Programe de test, tapez les commandes ci-dessus");
  dp.SetArticle(article);
  std::vector<std::string> footer;
  footer.push_back("Prefere STOP a Crt+c pour un arret propre");
  dp.SetFooter(footer);
  ic.setCallbackKeyboardInput(std::bind(callback, std::placeholders::_1));
  ic.setScanKeyboard(true);
  ic.StartScanKeyboard();
  dp.SetLoadingBar("1", 0);
  dp.SetLoadingBar("2", 0);
  ic.setLoadingBarActivate(true);
  ic.setWidthMax(100);
  ic.setBbrNav(4);
  ic.setKeyStop("STOP");
  ic.setKeyValueStart("<!");
  ic.setKeyValueStop("!>");
  ic.PrintScreen(dp);
  unsigned int loading1 = 0;
  unsigned int loading2 = 0;
  while (bRun) {
    loading1 += 1;
    loading2 += 2;
    if (loading1 > 100) {
      loading1 = 0;
    }
    if (loading2 > 100) {
      loading2 = 0;
    }
    dp.SetLoadingBar("1", loading1);
    dp.SetLoadingBar("2", loading2);
    ic.PrintScreen(dp);
    sleep(1);
  }
  ic.setScanKeyboard(false);
  ic.StopScanKeyboard();
  return 0;
}
