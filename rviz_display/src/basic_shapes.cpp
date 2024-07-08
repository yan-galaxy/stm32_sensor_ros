#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

void set_para(
visualization_msgs::Marker * sel_marker,
float posx,float posy,float posz,
float orix,float oriy,float oriz,float oriw,
float scax,float scay,float scaz,
float colorR,float colorG,float colorB,float colorAlpha)
{
    sel_marker->pose.position.x = posx;//0;
    sel_marker->pose.position.y = posy;//0;
    sel_marker->pose.position.z = posz;//0.25;

    sel_marker->pose.orientation.x = orix;//0.3;
    sel_marker->pose.orientation.y = oriy;//0.0;
    sel_marker->pose.orientation.z = oriz;//0.0;
    sel_marker->pose.orientation.w = oriw;//1;

    sel_marker->scale.x = scax;//2.0;
    sel_marker->scale.y = scay;//2.0;
    sel_marker->scale.z = scaz;//0.5;

    sel_marker->color.r = colorR;//0.0f;
    sel_marker->color.g = colorG;//1.0f;
    sel_marker->color.b = colorB;//0.0f;
    sel_marker->color.a = colorAlpha;//1.0;
}
void GrayToPseColor(uint16_t grayValue, float *colorR,float *colorG,float *colorB)
{
    // *colorR=(float)abs(0-grayValue)/256.0;
    // *colorG=(float)abs(127-grayValue)/256.0;
    // *colorB=(float)abs(255-grayValue)/256.0;

    if( (grayValue>=0) && (grayValue<=1023) )  
    {
        *colorR=0;
        *colorG=0;
        *colorB=(float)grayValue/1024.0;
    }
    else if( (grayValue>=1024) && (grayValue<=2047) )  
    {
        *colorR=0;
        *colorG=(float)(grayValue-1024)/1024.0;
        *colorB=(float)(2047-grayValue)/1024.0;
    }
    else if( (grayValue>=2048) && (grayValue<=3071) )  
    {
        *colorR=(float)(grayValue-2048)/1024.0;
        *colorG=1.0;
        *colorB=0;
    }
    else if( (grayValue>=3072) && (grayValue<=4095) )  
    {
        *colorR=1.0;
        *colorG=(float)(4095-grayValue)/1024.0;
        *colorB=0;
    }
}
int main( int argc, char** argv )
{
    uint8_t i,cnt=0;
    uint16_t color_cnt=0;
    
    ros::init(argc, argv, "basic_shapes");
    ros::NodeHandle n;
    ros::Rate r(1000);

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