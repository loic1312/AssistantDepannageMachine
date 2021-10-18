/**
 * @file DriverXml.h
 * @author PASSARET Loïc
 * @brief Gestion lecture fichier xml
 * @version 0.1
 * @date 2021-10-15
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef HEADER_DRIVERXML_H_
#define HEADER_DRIVERXML_H_

#include <boost/filesystem.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <string>
#include <iostream>

class DriverXml {
 private:
  std::string m_strPathXml;
  std::string m_strPathXsd;
  boost::property_tree::ptree m_ConfigTree;

 public:
  DriverXml(std::string strPathXml);
  ~DriverXml();

  void setPathXsd(std::string strPathXsd);

  bool ValidateXml();
  boost::property_tree::ptree LoadXml();
};

#endif  // HEADER_DRIVERXML_H_
