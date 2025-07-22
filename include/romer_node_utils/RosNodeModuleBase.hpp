/*
 File name: RosNodeModuleBase.hpp
 Author: Mehmet Efe Tiryaki
 E-mail: m.efetiryaki@gmail.com
 Date created: 12.02.2018
 Date last modified: 13.02.2019
 Date last modified: Updated for ROS 2
 */

#pragma once

#include <rclcpp/rclcpp.hpp>
#include <vector>
#include <functional>
#include <mutex>
#include <memory>


#include "romer_node_utils/RosNodeBase.hpp"

namespace romer_node_utils {

class RosNodeModuleBase : public RosNodeBase
{
 public:
  RosNodeModuleBase(const std::string& node_name) 
  : RosNodeBase(node_name), shutdownMutex_(std::make_unique<std::mutex>()), terminated_(false), terminate_(false)
  {

  }

  virtual ~RosNodeModuleBase() = default;

  virtual void create() override
  {
    RosNodeBase::create();
    terminated_ = false;
    terminate_ = false;
  }

  virtual void shutdown() override
  {
    terminate_ = true;
  }

  virtual void clean()
  {

  }

  bool isTerminated()
  {
    return terminated_;
  }

  void terminate()
  {
    terminated_ = true;
  }

  bool isTerminationStarted()
  {
    return terminate_;
  }

 protected:
  std::unique_ptr<std::mutex> shutdownMutex_;
  bool terminated_;
  bool terminate_;
};
}  // namespace romer_node_utils
