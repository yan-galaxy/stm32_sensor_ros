#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
 
int main( int argc, char** argv )
{
    ros::init(argc, argv, "basic_shapes");
    ros::NodeHandle n;
    ros::Rate r(1);
    ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

    uint32_t shape = visualization_msgs::Marker::CYLINDER;// CUBE SPHERE ARROW CYLINDER LINE_STRIP LINE_LIST CUBE_LIST SPHERE_LIST POINTS
    
    visualization_msgs::Marker marker[14];

    while (ros::ok())
    {
        

        marker[0].header.frame_id = "my_frame";
        marker[0].header.stamp = ros::Time::now();

        marker[0].ns = "basic_shapes0";
        marker[0].id = 0;

        marker[0].type = shape;

        marker[0].action = visualization_msgs::Marker::MODIFY; // ADD MODIFY DELETE DELETEALL

        marker[0].pose.position.x = 0;
        marker[0].pose.position.y = 0;
        marker[0].pose.position.z = 0.25;
        marker[0].pose.orientation.x = 0.0;
        marker[0].pose.orientation.y = 0.0;
        marker[0].pose.orientation.z = 0.0;
        marker[0].pose.orientation.w = 1.0;

        marker[0].scale.x = 2.0;
        marker[0].scale.y = 2.0;
        marker[0].scale.z = 0.5;

        marker[0].color.r = 0.0f;
        marker[0].color.g = 1.0f;
        marker[0].color.b = 0.0f;
        marker[0].color.a = 1.0;

        marker[0].lifetime = ros::Duration();

        marker[1].header.frame_id = "my_frame";
        marker[1].header.stamp = ros::Time::now();

        marker[1].ns = "basic_shapes1";
        marker[1].id = 1;

        marker[1].type = shape;

        marker[1].action = visualization_msgs::Marker::MODIFY; // ADD MODIFY DELETE DELETEALL

        marker[1].pose.position.x = 2;
        marker[1].pose.position.y = 2;
        marker[1].pose.position.z = 0.25;
        marker[1].pose.orientation.x = 0.0;
        marker[1].pose.orientation.y = 0.0;
        marker[1].pose.orientation.z = 0.0;
        marker[1].pose.orientation.w = 1.0;

        marker[1].scale.x = 1.0;
        marker[1].scale.y = 1.0;
        marker[1].scale.z = 0.5;

        marker[1].color.r = 1.0f;
        marker[1].color.g = 0.0f;
        marker[1].color.b = 0.0f;
        marker[1].color.a = 1.0;

        marker[1].lifetime = ros::Duration();

        marker[2].header.frame_id = "my_frame";
        marker[2].header.stamp = ros::Time::now();

        marker[2].ns = "basic_shapes2";
        marker[2].id = 2;

        marker[2].type = shape;

        marker[2].action = visualization_msgs::Marker::MODIFY; // ADD MODIFY DELETE DELETEALL

        marker[2].pose.position.x = 4;
        marker[2].pose.position.y = 4;
        marker[2].pose.position.z = 0.25;
        marker[2].pose.orientation.x = 0.0;
        marker[2].pose.orientation.y = 0.0;
        marker[2].pose.orientation.z = 0.0;
        marker[2].pose.orientation.w = 1.0;

        marker[2].scale.x = 1.0;
        marker[2].scale.y = 1.0;
        marker[2].scale.z = 0.5;

        marker[2].color.r = 0.0f;
        marker[2].color.g = 0.0f;
        marker[2].color.b = 1.0f;
        marker[2].color.a = 1.0;

        marker[2].lifetime = ros::Duration();

        // while (marker_pub.getNumSubscribers() < 1)
        // {
        //     if (!ros::ok())
        //     {
        //         return 0;
        //     }
        //     ROS_WARN_ONCE("Please create a subscriber to the marker");
        //     sleep(1);
        // }
        marker_pub.publish(marker[0]);
        marker_pub.publish(marker[1]);
        marker_pub.publish(marker[2]);

        r.sleep();
    }
}