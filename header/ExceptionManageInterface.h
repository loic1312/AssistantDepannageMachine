/**
 * @file ExceptionManageInterface.h
 * @author passaret loic
 * @brief gestion exception manage interface
 * @version 0.1
 * @date 2021-06-17
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef HEADER_EXCEPTIONMANAGEINTERFACE_H_
#define HEADER_EXCEPTIONMANAGEINTERFACE_H_

#include <exception>
#include <string>

class ExceptionManageInterface : public std::exception {
 public:
  explicit ExceptionManageInterface(std::string strMsg) {
    strMsgException = strMsg;
  }
  const char* what() { return strMsgException.c_str(); }

 private:
  std::string strMsgException;
};

#endif  // HEADER_EXCEPTIONMANAGEINTERFACE_H_
