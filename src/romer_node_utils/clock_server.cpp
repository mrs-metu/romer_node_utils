#include <romer_node_utils/RosNodeLauncher.hpp>
#include <romer_node_utils/ClockServer.hpp>


int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  using namespace romer_node_utils;
  auto node = std::make_shared<rclcpp::Node>("clock_server");
  auto nodeLauncher = std::make_shared<RosNodeLauncher<ClockServer>>(node);
  romer_node_utils::CONFIRM("Clock Server initialized.");
  nodeLauncher->run();
  rclcpp::shutdown();
  return 0;
}
