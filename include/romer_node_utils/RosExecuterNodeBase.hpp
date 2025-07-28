/*
 File name: RosExecuterNodeBase.hpp
 Author: Mehmet Efe Tiryaki
 E-mail: m.efetiryaki@gmail.com
 Date created: 1.07.2018
 Date last modified: 1.07.2018
 Date last modified: Updated for ROS 2
 */
#pragma once

#include "RosNodeBase.hpp"


namespace romer_node_utils {

class RosExecuterNodeBase : public RosNodeBase
{
 public:
  RosExecuterNodeBase(const std::string& node_name):
    RosNodeBase(node_name)
  {

  };

  virtual ~RosExecuterNodeBase() = default;

  virtual void initialize() override
  {
    // init Publishers
    initializePublishers();
    // init Subscribers
    initializeSubscribers();
    // init Services
    initializeServices();
    // init Action Services
    initializeActionServers();
  }

  virtual void execute() override
  {
  }



};
}  // namespace romer_node_utils
