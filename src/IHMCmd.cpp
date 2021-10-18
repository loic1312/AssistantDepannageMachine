#include "IHMCmd.h"

IHMCmd::IHMCmd() {}

IHMCmd::~IHMCmd() {}

void IHMCmd::Display(std::string strMsg) {
    std::system("clear");
    std::cout << strMsg << std::endl;
}

std::string IHMCmd::GetData(std::string strIssue) {
    std::string strData;
    std::system("clear");
    std::cout << strIssue << std::endl;
    std::cin >> strData;
    return strData;
}
