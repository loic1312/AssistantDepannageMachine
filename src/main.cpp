#include <unistd.h>

#include <chrono>
#include <iostream>
#include <thread>

#include "DTODataPrint.h"
#include "InterfaceCmd.h"

bool bRun = true;
DTODataPrint dp;
InterfaceCmd ic;
void callback(std::string data) {
  if (data == "STOP") {
    std::vector<std::string> article;
    article.push_back("Programe de test, termine");
    dp.SetArticle(article);
    ic.PrintScreen(dp);
    bRun = false;
  } else if (data == "Print") {
    std::vector<std::string> article;
    article.push_back("Programe de test, tapez les commandes ci-dessus");
    dp.SetArticle(article);
    ic.PrintScreen(dp);
  } else if (data == "Loading") {
    unsigned int uiCpt = 0;
    ic.setLoadingActivate(true);
    std::vector<std::string> article;
    article.push_back("Calcul en cours...");
    dp.SetArticle(article);
    ic.PrintScreen(dp);
    while (uiCpt < 5) {
      uiCpt += 1;
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    ic.setLoadingActivate(false);
    article.clear();
    article.push_back("Programe de test, tapez les commandes ci-dessus");
    dp.SetArticle(article);
    ic.PrintScreen(dp);
  } else if (data == "UpLoad") {
    unsigned int loading1 = 0;
    unsigned int loading2 = 0;
    dp.SetLoadingBar("1", 0);
    dp.SetLoadingBar("2", 0);
    ic.setLoadingBarActivate(true);
    std::vector<std::string> article;
    article.push_back("Telechargment en cour...");
    dp.SetArticle(article);
    while (loading1 < 100 || loading2 < 100) {
      loading1 += 1;
      loading2 += 2;
      if (loading1 > 100) {
        loading1 = 100;
      }
      if (loading2 > 100) {
        loading2 = 100;
      }
      dp.SetLoadingBar("1", loading1);
      dp.SetLoadingBar("2", loading2);
      ic.PrintScreen(dp);
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    ic.setLoadingBarActivate(false);
    article.clear();
    article.push_back("Programe de test, tapez les commandes ci-dessus");
    dp.SetArticle(article);
    ic.PrintScreen(dp);
  } else if (data == "Graph") {
    float fx = -10;
    float fy = -15;
    for (unsigned int i = 0; i <= 40; ++i) {
      dp.SetPointGraphic(fx, fy);
      fx = fx + 0.5;
      fy = fy + 0.5;
    }
    std::vector<std::string> article;
    article.push_back("Une courbe:");
    dp.SetArticle(article);
    ic.setPrintGraphic(true);
    ic.setHeigthGraph(10);
    ic.PrintScreen(dp);
    ic.setPrintGraphic(false);
  } else if (data == "Table") {
    std::vector<std::string> article;
    article.push_back("En chantier");
    dp.SetArticle(article);
    ic.PrintScreen(dp);
  } else {
    std::vector<std::string> article;
    article.push_back("Programe de test, tapez les commandes ci-dessus");
    article.push_back("Command inconnue");
    dp.SetArticle(article);
    ic.PrintScreen(dp);
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
  nav.push_back("Loading");
  nav.push_back("UpLoad");
  nav.push_back("Graph");
  nav.push_back("Table");
  std::map<float, float> mGraph;
  float ymin = -10;
  float ymax = 10;
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
  ic.setWidthMax(50);
  ic.setBbrNav(4);
  ic.setKeyStop("STOP");
  ic.setKeyValueStart("<!");
  ic.setKeyValueStop("!>");
  ic.PrintScreen(dp);
  while (bRun) {
    sleep(1);
  }
  ic.setScanKeyboard(false);
  ic.StopScanKeyboard();
  return 0;
}
