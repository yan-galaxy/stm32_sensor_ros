/***********************************************************************
Copyright 2020 GuYueHome (www.guyuehome.com).
***********************************************************************/

/**
 * 该例程将订阅/person_info话题，自定义消息类型learning_topic::Person
 */
 
#include <ros/ros.h>
#include "uart_stm32/stm32data.h"

// 接收到订阅的消息后，会进入消息回调函数
void stm32dataInfoCallback(const uart_stm32::stm32data::ConstPtr& msg)
{
    // 将接收到的消息打印出来
    ROS_INFO("Subcribe stm32data Info: 00:%d  01:%d  02:%d", 
			 msg->voltage00, msg->voltage01, msg->voltage02);
}

int main(int argc, char **argv)
{
    // 初始化ROS节点
    ros::init(argc, argv, "person_subscriber");

    // 创建节点句柄
    ros::NodeHandle n;

    // 创建一个Subscriber，订阅名为/person_info的topic，注册回调函数personInfoCallback
    ros::Subscriber person_info_sub = n.subscribe("/stm32data_info", 38, stm32dataInfoCallback);

    // 循环等待回调函数
    ros::spin();

    return 0;
}
