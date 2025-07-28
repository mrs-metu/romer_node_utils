/*@file
 File name: romer_node_utils.hpp
 Author: Mehmet Efe Tiryaki
 E-mail: m.efetiryaki@gmail.com
 Date created: 12.02.2019
 Date last modified: 21.03.2019
 */
#pragma once

#include <Eigen/Dense>
#include <Eigen/SparseCore>

#include <functional>
#include <rclcpp/rclcpp.hpp>
#include <string>
#include <unordered_map>
#include <vector>

namespace romer_node_utils {

inline bool ERROR(std::string text) {
  std::cout << "\033[0;91m" << text << "\033[0m" << std::endl;
  return false;
}

inline bool WARNING(std::string text) {
  std::cout << "\033[0;93m" << text << "\033[0m" << std::endl;
  return true;
}

inline bool CONFIRM(std::string text) {
  std::cout << "\033[0;92m" << text << "\033[0m" << std::endl;
  return true;
}

inline bool paramRead(rclcpp::Node& node_, const std::string& paramName,
  rclcpp::Parameter& variable) {
  // std::cerr << "\033[0;32m" << paramName << "\033[0m" << std::endl;
  if (node_.has_parameter(paramName)) {
    node_.get_parameter(paramName, variable);
  } else {
  return ERROR(paramName + " is not found. ");
  }
  return true;
  // std::cerr << "\033[0;31m" << variable << "\033[0m" << std::endl;
}

/* Example usage of above:
rclcpp::Parameter param;
paramRead(node, "param_name", param);

// Instead of separate methods, you can get any type:
bool b = param.as_bool();                    // replaces bool overload
int i = param.as_int();                      // replaces int overload
double d = param.as_double();                // replaces double overload
std::string s = param.as_string();           // replaces string overload
std::vector<int> vi = param.as_integer_array();     // replaces vector<int> overload
std::vector<double> vd = param.as_double_array();   // replaces vector<double> overload
std::vector<std::string> vs = param.as_string_array(); // replaces vector<string> overload
*/

inline bool paramRead(const rclcpp::Node& node_, const std::string& paramName,
                     Eigen::MatrixXd& variable) {
    rclcpp::Parameter param;
    if (node_.has_parameter(paramName)) {
        node_.get_parameter(paramName, param);
        std::vector<double> buffer = param.as_double_array();
        int prevSize = variable.rows();
        variable = Eigen::MatrixXd::Zero(buffer.size(), buffer.size());
        variable.diagonal() << Eigen::Map<Eigen::VectorXd>(&buffer[0], buffer.size());
        
        if (prevSize != variable.rows()) {
            return WARNING(paramName + " has changed the matrix size from " +
                         std::to_string(prevSize) + "x" + std::to_string(prevSize) +
                         " to " + std::to_string(variable.rows()) + "x" +
                         std::to_string(variable.rows()));
        }
        return true;
    }
    return ERROR(paramName + " is not found. ");
}

inline bool paramRead(const rclcpp::Node& node_, const std::string& paramName,
                     Eigen::VectorXd& variable) {
    rclcpp::Parameter param;
    if (node_.has_parameter(paramName)) {
        node_.get_parameter(paramName, param);
        std::vector<double> buffer = param.as_double_array();
        int prevSize = variable.size();
        variable = Eigen::VectorXd::Zero(buffer.size());
        for (size_t i = 0; i < buffer.size(); i++) {
            variable[i] = buffer[i];
        }
        
        if (prevSize != variable.size()) {
            return WARNING(paramName + " has changed the vector size from " +
                         std::to_string(prevSize) + " to " +
                         std::to_string(variable.size()));
        }
        return true;
    }
    return ERROR(paramName + " is not found. ");
}

template<int N>
inline bool paramRead(const rclcpp::Node& node_, const std::string& paramName,
                     Eigen::Matrix<double, N, 1>& variable) {
    rclcpp::Parameter param;
    if (node_.has_parameter(paramName)) {
        node_.get_parameter(paramName, param);
        std::vector<double> buffer = param.as_double_array();
        if (buffer.size() != N) {
            return ERROR(paramName + " size mismatch. Expected " + 
                        std::to_string(N) + " got " + std::to_string(buffer.size()));
        }
        variable = Eigen::Matrix<double, N, 1>::Zero();
        for (int i = 0; i < N; i++) {
            variable[i] = buffer[i];
        }
        return true;
    }
    return ERROR(paramName + " is not found. ");
}

inline bool paramRead(const rclcpp::Node& node_, const std::string& paramName,
                     Eigen::Quaterniond& variable) {
    rclcpp::Parameter param;
    if (node_.has_parameter(paramName)) {
        node_.get_parameter(paramName, param);
        std::vector<double> buffer = param.as_double_array();
        if (buffer.size() != 4) {
            return ERROR(paramName + " is not a Quaternion ");
        }
        variable = Eigen::Quaterniond(buffer[0], buffer[1], buffer[2], buffer[3]);
        return true;
    }
    return ERROR(paramName + " is not found. ");
}

inline bool paramRead(const rclcpp::Node& node_, const std::string& paramName,
                     Eigen::SparseMatrix<double, Eigen::RowMajor>& variableSpace) {
    rclcpp::Parameter param;
    if (node_.has_parameter(paramName)) {
        node_.get_parameter(paramName, param);
        std::vector<double> buffer = param.as_double_array();
        Eigen::MatrixXd dense = Eigen::MatrixXd::Zero(buffer.size(), buffer.size());
        dense.diagonal() << Eigen::Map<Eigen::VectorXd>(&buffer[0], buffer.size());
        variableSpace = dense.sparseView();
        return true;
    }
    return ERROR(paramName + " is not found. ");
}

} // namespace romer_node_utils
