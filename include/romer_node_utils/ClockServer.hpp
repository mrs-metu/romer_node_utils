/*
 File name: ClockServer.hpp
 Author: Mehmet Efe Tiryaki, Ege Ecevit
 E-mail: m.efetiryaki@gmail.com
 Date created: 19.06.2018
 Date last modified: 13.02.2019
 Date last modified: Updated for ROS 2
 */
#pragma once


#include <memory>
#include <mutex>
#include <thread>
#include <chrono>

#include <rclcpp/rclcpp.hpp>
#include <rosgraph_msgs/msg/clock.hpp>
#include "RosNodeModuleBase.hpp"

namespace romer_node_utils {

class ClockServer : public RosNodeModuleBase
{
 public:
  ClockServer(rclcpp::Node::SharedPtr node)
      : RosNodeModuleBase(node), startTime_(0)
  {
  }

  virtual ~ClockServer() = default;

  void create() override
  {
    clockRate_ = 1000;
    rate_ = std::make_shared<rclcpp::Rate>(clockRate_);
    startTime_ = getNode()->now().seconds();
  }

  void initializePublishers() override
  {
    clockPublisher_ = getNode()->create_publisher<rosgraph_msgs::msg::Clock>("/clock", 10);
  }

  void advance()
  {
    timeNow_ =   getNode()->now().seconds() - startTime_;
    auto msg = std::make_unique<rosgraph_msgs::msg::Clock>();
    msg->clock = rclcpp::Time(timeNow_ * 1e9); // Convert to nanoseconds
    clockPublisher_->publish(std::move(msg));
  }

  void execute() override
  {
    while (rclcpp::ok()) {
      if (!isTerminationStarted()) {
        advance();
        rate_->sleep();
      } else {
        break;
      }
    }
  }

  void start() override
  {
    timeThread_ = std::make_unique<std::thread>([this]() {this->execute();});
  }

  void stop() override
  {
    if (timeThread_ && timeThread_->joinable()) 
    {
      timeThread_->join();
    }
  }

  void shutdown() override
  {
    RosNodeModuleBase::shutdown();
    stop();
  }

 protected:
  double startTime_ ;
  double timeNow_ ;
  double clockRate_;

  std::unique_ptr<std::thread> timeThread_;
  std::shared_ptr<rclcpp::Publisher<rosgraph_msgs::msg::Clock>> clockPublisher_;
  std::shared_ptr<rclcpp::Rate> rate_;
};
} // namespace romer_node_utils