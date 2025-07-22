/*
 File name: RosNodeLauncher.hpp
 Author: Mehmet Efe Tiryaki
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

#include <romer_node_utils/RosNodeBase.hpp>
#include <romer_node_utils/RosNodeModuleBase.hpp>
#include <std_srvs/srv/empty.hpp>

namespace romer_node_utils
{

inline rclcpp::Node::SharedPtr ROSINITIALIZE(const std::string &node_name)
{
    int argc = 0;
    char **argv = {};
    if (!rclcpp::is_initialized())
    {
        rclcpp::init(argc, argv);
    }
    return rclcpp::Node::make_shared(node_name);
};

template <typename NodeType> class RosNodeLauncher : public RosNodeModuleBase
{
    public:
        RosNodeLauncher(const std::string &node_name)
            : RosNodeModuleBase(node_name)
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
            RosNodeModuleBase::create();
            node_ = std::make_shared<NodeType>(node_name);
            node_->create();
            // WARNING("create : [RosNodeLauncher]");
        }

        // Reading parameters
        void readParameters() override
        {
            RosNodeModuleBase::readParameters();
            node_->readParameters();
            // WARNING("readParameters : [RosNodeLauncher]");
        }

        // initize class variables
        void initialize() override
        {
            RosNodeModuleBase::initialize();
            node_->initialize();
            // WARNING("initialize : [RosNodeLauncher]");
        }

        // shutdown class variables
        void shutdown() override
        {
            RosNodeModuleBase::shutdown();
            node_->shutdown();
            // WARNING("shutdown : [RosNodeLauncher]");
        }

        // init Publisher
        void initializePublishers() override
        {
            RosNodeModuleBase::initializePublishers();
            node_->initializePublishers();
            // WARNING("initializePublishers : [RosNodeLauncher]");
        }

        // init Subscribers
        void initializeSubscribers() override
        {
            RosNodeModuleBase::initializeSubscribers();
            node_->initializeSubscribers();
            // WARNING("initializeSubscribers : [RosNodeLauncher]");
        }

        // init Subscribers
        void initializeServices() override
        {
            RosNodeModuleBase::initializeServices();
            node_->initializeServices();
            nodeRestartServices_ = this->create_service<std_srvs::srv::Empty>(
                "~/restart",
                std::bind(&RosNodeLauncher::nodeRestartCallback, this,
                          std::placeholders::_1, std::placeholders::_2));
            // WARNING("initializeServices : [RosNodeLauncher]");
        }

        void run() { rclcpp::spin(shared_from_this()); }

        void restart()
        {
            node_->shutdown();
            node_ = std::make_shared<NodeType>(node_name);
            node_->create();
            node_->readParameters();
            node_->initializePublishers();
            node_->initializeSubscribers();
            node_->initializeServices();
            node_->initialize();
            node_->start();
        }

        void nodeRestartCallback(
            const std::shared_ptr<std_srvs::srv::Empty::Request>,
            std::shared_ptr<std_srvs::srv::Empty::Response>)
        {
            restart();
        }

    protected:
        typename rclcpp::Service<std_srvs::srv::Empty>::SharedPtr
            restart_service_;
        std::shared_ptr<RosNodeBase> node_;
};
} // namespace romer_node_utils
