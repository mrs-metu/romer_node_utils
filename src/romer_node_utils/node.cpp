#include <iostream>
#include <memory>
#include <romer_node_utils/romer_node_utils.hpp>
#include <romer_node_utils/RosNodeLauncher.hpp>
#include <romer_node_utils/RosNodeModuleBase.hpp>


int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  using namespace romer_node_utils;
  auto node = std::make_shared<rclcpp::Node>("launcher_node");
  auto launcher = std::make_shared<RosNodeLauncher<RosNodeModuleBase>>(node);
  romer_node_utils::CONFIRM("Launcher initialized.");
  launcher->run();
  rclcpp::shutdown();
  return 0;
}
