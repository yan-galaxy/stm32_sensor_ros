#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "head.h"



int main( int argc, char** argv )
{
    uint8_t i,cnt=0;
    uint16_t color_cnt=0;
    
    ros::init(argc, argv, "basic_shapes");
    ros::NodeHandle n,n2;
    ros::Rate r(1000);

    // ros::Publisher stm32data_info_pub = n2.advertise<uart_stm32::stm32data>("/stm32data_info", 38);
    ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

    uint32_t shape = visualization_msgs::Marker::CYLINDER;// CUBE SPHERE ARROW CYLINDER LINE_STRIP LINE_LIST CUBE_LIST SPHERE_LIST POINTS
    
    visualization_msgs::Marker marker[14];
    for(i=0;i<14;i++)
    {
        marker[i].header.frame_id = "sensor";
        marker[i].header.stamp = ros::Time::now();
        marker[i].ns = "basic_shapes";
        marker[i].id = i;
        marker[i].type = shape;
        marker[i].action = visualization_msgs::Marker::MODIFY; // ADD MODIFY DELETE DELETEALL
        marker[i].lifetime = ros::Duration();
    }

    while (ros::ok())
    {
        set_para(&marker[0],
        6.0, 0.0, 0.1,             //pose.position.x y z
        0.0, 0.0, 0.0, 1.0,         //pose.orientation.x y z w
        1.0, 1.0, 0.2,              //scale.x y z
        0.0f, 1.0f, 0.0f, 1.0       //color.r g b a
        );
        set_para(&marker[1],
        6.0, 2.0, 0.1,             //pose.position.x y z
        0.0, 0.0, 0.0, 1.0,         //pose.orientation.x y z w
        1.0, 1.0, 0.2,              //scale.x y z
        1.0f, 0.0f, 0.0f, 1.0       //color.r g b a
        );
        set_para(&marker[2],
        4.0, 2.0, 0.1,             //pose.position.x y z
        0.0, 0.0, 0.0, 1.0,         //pose.orientation.x y z w
        1.0, 1.0, 0.2,              //scale.x y z
        0.0f, 0.0f, 1.0f, 1.0       //color.r g b a
        );
        set_para(&marker[3],
        2.0, 2.0, 0.1,             //pose.position.x y z
        0.0, 0.0, 0.0, 1.0,         //pose.orientation.x y z w
        1.0, 1.0, 0.2,              //scale.x y z
        1.0f, 0.0f, 1.0f, 1.0       //color.r g b a
        );
        set_para(&marker[4],
        7.0, 5.0, 0.1,             //pose.position.x y z
        0.0, 0.0, 0.0, 1.0,         //pose.orientation.x y z w
        1.0, 1.0, 0.2,              //scale.x y z
        1.0f, 0.0f, 1.0f, 1.0       //color.r g b a
        );
        set_para(&marker[5],
        7.0, 8.0, 0.1,             //pose.position.x y z
        0.0, 0.0, 0.0, 1.0,         //pose.orientation.x y z w
        1.0, 1.0, 0.2,              //scale.x y z
        1.0f, 0.0f, 1.0f, 1.0       //color.r g b a
        );
        set_para(&marker[6],
        5.0, 5.0, 0.1,             //pose.position.x y z
        0.0, 0.0, 0.0, 1.0,         //pose.orientation.x y z w
        1.0, 1.0, 0.2,              //scale.x y z
        1.0f, 0.0f, 1.0f, 1.0       //color.r g b a
        );
        set_para(&marker[7],
        5.0, 8.0, 0.1,             //pose.position.x y z
        0.0, 0.0, 0.0, 1.0,         //pose.orientation.x y z w
        1.0, 1.0, 0.2,              //scale.x y z
        1.0f, 0.0f, 1.0f, 1.0       //color.r g b a
        );
        set_para(&marker[8],
        3.0, 5.0, 0.1,             //pose.position.x y z
        0.0, 0.0, 0.0, 1.0,         //pose.orientation.x y z w
        1.0, 1.0, 0.2,              //scale.x y z
        1.0f, 0.0f, 1.0f, 1.0       //color.r g b a
        );
        set_para(&marker[9],
        3.0, 8.0, 0.1,             //pose.position.x y z
        0.0, 0.0, 0.0, 1.0,         //pose.orientation.x y z w
        1.0, 1.0, 0.2,              //scale.x y z
        1.0f, 0.0f, 1.0f, 1.0       //color.r g b a
        );
        set_para(&marker[10],
        1.0, 5.0, 0.1,             //pose.position.x y z
        0.0, 0.0, 0.0, 1.0,         //pose.orientation.x y z w
        1.0, 1.0, 0.2,              //scale.x y z
        1.0f, 0.0f, 1.0f, 1.0       //color.r g b a
        );
        set_para(&marker[11],
        1.0, 8.0, 0.1,             //pose.position.x y z
        0.0, 0.0, 0.0, 1.0,         //pose.orientation.x y z w
        1.0, 1.0, 0.2,              //scale.x y z
        1.0f, 0.0f, 1.0f, 1.0       //color.r g b a
        );
        set_para(&marker[12],
        0.0, 0.0, 0.1,             //pose.position.x y z
        0.0, 0.0, 0.0, 1.0,         //pose.orientation.x y z w
        1.0, 1.0, 0.2,              //scale.x y z
        1.0f, 0.0f, 1.0f, 1.0       //color.r g b a
        );
        set_para(&marker[13],
        -2.0, 0.0, 0.1,             //pose.position.x y z
        0.0, 0.0, 0.0, 1.0,         //pose.orientation.x y z w
        1.0, 1.0, 0.2,              //scale.x y z
        1.0f, 0.0f, 1.0f, 1.0       //color.r g b a
        );
        

        GrayToPseColor(color_cnt,&marker[3].color.r,&marker[3].color.g,&marker[3].color.b);
        if(cnt==3)
        {
            if(color_cnt>=4095) color_cnt=0;
            else color_cnt+=4;
        }
        

        while (marker_pub.getNumSubscribers() < 1)
        {
            if (!ros::ok())
            {
                return 0;
            }
            ROS_WARN_ONCE("Please create a subscriber to the marker");
            // sleep(1);
        }

        marker_pub.publish(marker[cnt]);
        if(cnt>=13)cnt=0;
        else cnt++;

        // for(i=0;i<14;i++)marker_pub.publish(marker[i]);

        r.sleep();
    }
}
