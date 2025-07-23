#include <iostream>
#include <memory>
#include "romer_node_utils/RosExecuterNodeBase.hpp"
#include "romer_node_utils/romer_node_utils.hpp"
#include "romer_node_utils/RosNodeLauncher.hpp"


int main(int argc, char **argv)
{
  /*
  rclcpp::init(argc, argv);
  auto node = std::make_shared<romer_node_utils::RosExecuterNodeBase>("romer_executer_node");
  node->initialize();
  node->execute();
  romer_node_utils::CONFIRM("node initialized and executing.");
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
  */
  /*
  auto node = romer_node_utils::ROSINITIALIZE("estimator_launcher");
  romer_node_utils::RosNodeLauncher<romer_node_utils::RosNodeModuleBase> launcher("estimator_node");
  launcher.run();
  romer_node_utils::CONFIRM("Launcher/node initialized and executing.");
  return 0;
  */
  rclcpp::init(argc, argv);
  auto launcher = std::make_shared<romer_node_utils::RosNodeLauncher<romer_node_utils::RosNodeModuleBase>>("estimator_node");
  romer_node_utils::CONFIRM("Launcher initialized.");
  launcher->run();
  rclcpp::shutdown();
  return 0;
}
