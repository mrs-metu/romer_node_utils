/*
 File name: RosNodeLauncher.hpp
 Author: Mehmet Efe Tiryaki, Ege Ecevit
 E-mail: m.efetiryaki@gmail.com
 Date created: 24.06.2019
 Date last modified: 24.06.2019
 Date last modified: Updated for ROS 2
 */
#pragma once

#include <functional>
#include <memory>
#include <rclcpp/rclcpp.hpp>
#include <vector>

#include "RosNodeModuleBase.hpp"
#include <std_srvs/srv/empty.hpp>

namespace romer_node_utils
{

template <typename NodeType> 
class RosNodeLauncher : public RosNodeModuleBase
{
    public:
        RosNodeLauncher(rclcpp::Node::SharedPtr node)
            : RosNodeModuleBase(node)
        {
            create();
            readParameters();
            initializePublishers();
            initializeSubscribers();
            initializeServices();
            initialize();
            node_->start();
        }

        ~RosNodeLauncher() = default;

        // Create the objects in this class
        void create() override
        {
            node_ = std::make_shared<NodeType>(getNode());
            node_->create();
        }

        // Reading parameters
        void readParameters() override
        {
            node_->readParameters();
        }

        // initize class variables
        void initialize() override
        {
            node_->initialize();
        }

        // shutdown class variables
        void shutdown() override
        {
            node_->shutdown();
        }

        // init Publisher
        void initializePublishers() override
        {
            node_->initializePublishers();
        }

        // init Subscribers
        void initializeSubscribers() override
        {
            node_->initializeSubscribers();
        }

        // init Services
        void initializeServices() override
        {
            node_->initializeServices();
        }

        void run() { 
            rclcpp::Rate loop_rate(2000); // 2000 Hz frequency
            while (rclcpp::ok()) {
                rclcpp::spin_some(getNode()); // spin_some spins the node processes available callbacks and returns no blocking
                loop_rate.sleep(); // sleep for the remaining time to maintain the 2000 Hz frequency
            }
        }

        void restart()
        {
            node_->shutdown();
            node_ = std::make_shared<NodeType>(getNode());
            node_->create();
            node_->readParameters();
            node_->initializePublishers();
            node_->initializeSubscribers();
            node_->initializeServices();
            node_->initialize();
            node_->start();
        }

    protected:
        std::shared_ptr<RosNodeModuleBase> node_;
};
} // namespace romer_node_utils
