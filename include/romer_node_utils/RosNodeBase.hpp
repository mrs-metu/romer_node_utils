/*
 File name: RosNodeBase.hpp
 Author: Mehmet Efe Tiryaki
 E-mail: m.efetiryaki@gmail.com
 Date created: 1.07.2018
 Date last modified: Updated for ROS 2
 */
#pragma once

#include <rclcpp/rclcpp.hpp>
#include <vector>
#include <unordered_map>
#include <functional>
#include <memory>

#include <romer_node_utils/romer_node_utils.hpp>

namespace romer_node_utils {

class RosNodeBase : public rclcpp::Node
{
 public:
  RosNodeBase(const std::string& node_name) : Node(node_name) {}

  virtual ~RosNodeBase() = default; // Tells the compiler to generate default destructor implementation


  // Create the objects in this class
  virtual void create()
  {

  }

  // Reading parameters
  virtual void readParameters()
  {

  }

  // initize class variables
  virtual void initialize()
  {

  }

  // shutdown class variables
  virtual void shutdown()
  {

  }


  // init Publisher
  virtual void initializePublishers()
  {

  }

  // init Subscribers
  virtual void initializeSubscribers()
  {

  }

  // init Services
  virtual void initializeServices()
  {

  }

  // init Services
  virtual void initializeActionServers()
  {

  }


  virtual void execute()
  {

  }

  virtual void start()
  {

  }

  virtual void stop()
  {

  }

};
}  // namespace romer_node_utils
