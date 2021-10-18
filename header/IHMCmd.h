#ifndef HEADER_IHMCMD_H_
#define HEADER_IHMCMD_H_

#include <string>
#include <iostream>
#include <stdlib.h>

class IHMCmd
{
private:
public:
    IHMCmd();
    ~IHMCmd();

    void Display(std::string strMsg);
    std::string GetData(std::string strIssue);
};

#endif // HEADER_IHMCMD_H_
