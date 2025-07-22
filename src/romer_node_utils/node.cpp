#include <iostream>
#include <memory>
#include "romer_node_utils/RosExecuterNodeBase.hpp"
#include "romer_node_utils/romer_node_utils.hpp"

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<romer_node_utils::RosExecuterNodeBase>("romer_executer_node");
  node->initialize();
  node->execute();
  romer_node_utils::CONFIRM("node initialized and executing.");
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
