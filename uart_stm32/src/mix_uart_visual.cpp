#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <iostream>
#include <thread>
#include "head.h"
#include "uart_stm32/stm32data.h"
#include <mutex>
#include <stdlib.h>
#include "WzSerialportPlus.h"
#include <queue>
#include <unistd.h> 

using namespace std;
bool serial_open;
queue<char> Queue;
uint32_t right_cnt;
uint32_t wrong_cnt;

uart_stm32::stm32data stm32data_msg;
visualization_msgs::Marker marker[14];
mutex mtx;//互斥锁


void visual_proj(ros::Publisher pub,ros::Rate rosrate)
{
    uint8_t i,cnt=0;
    uint16_t color_cnt=0;

    uint32_t shape = visualization_msgs::Marker::CYLINDER;// CUBE SPHERE ARROW CYLINDER LINE_STRIP LINE_LIST CUBE_LIST SPHERE_LIST POINTS
    
    mtx.lock();
    ROS_INFO("visual_thread run success\r\n");
    mtx.unlock();
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
    set_para(&marker[0],
    6.0, 0.0, 0.1,             //pose.position.x y z
    0.0, 0.0, 0.0, 1.0,         //pose.orientation.x y z w
    1.0, 1.0, 0.2,              //scale.x y z
    0.0f, 1.0f, 0.0f, 1.0       //color.r g b a
    );
    set_para(&marker[10],
    6.0, 2.0, 0.1,             //pose.position.x y z
    0.0, 0.0, 0.0, 1.0,         //pose.orientation.x y z w
    1.0, 1.0, 0.2,              //scale.x y z
    1.0f, 0.0f, 0.0f, 1.0       //color.r g b a
    );
    set_para(&marker[11],
    4.0, 2.0, 0.1,             //pose.position.x y z
    0.0, 0.0, 0.0, 1.0,         //pose.orientation.x y z w
    1.0, 1.0, 0.2,              //scale.x y z
    0.0f, 0.0f, 1.0f, 1.0       //color.r g b a
    );
    set_para(&marker[12],
    2.0, 2.0, 0.1,             //pose.position.x y z
    0.0, 0.0, 0.0, 1.0,         //pose.orientation.x y z w
    1.0, 1.0, 0.2,              //scale.x y z
    1.0f, 0.0f, 1.0f, 1.0       //color.r g b a
    );
    set_para(&marker[7],
    7.0, 5.0, 0.1,             //pose.position.x y z
    0.0, 0.0, 0.0, 1.0,         //pose.orientation.x y z w
    1.0, 1.0, 0.2,              //scale.x y z
    1.0f, 0.0f, 1.0f, 1.0       //color.r g b a
    );
    set_para(&marker[6],
    7.0, 8.0, 0.1,             //pose.position.x y z
    0.0, 0.0, 0.0, 1.0,         //pose.orientation.x y z w
    1.0, 1.0, 0.2,              //scale.x y z
    1.0f, 0.0f, 1.0f, 1.0       //color.r g b a
    );
    set_para(&marker[13],
    5.0, 5.0, 0.1,             //pose.position.x y z
    0.0, 0.0, 0.0, 1.0,         //pose.orientation.x y z w
    1.0, 1.0, 0.2,              //scale.x y z
    1.0f, 0.0f, 1.0f, 1.0       //color.r g b a
    );
    set_para(&marker[5],
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
    set_para(&marker[4],
    3.0, 8.0, 0.1,             //pose.position.x y z
    0.0, 0.0, 0.0, 1.0,         //pose.orientation.x y z w
    1.0, 1.0, 0.2,              //scale.x y z
    1.0f, 0.0f, 1.0f, 1.0       //color.r g b a
    );
    set_para(&marker[2],
    1.0, 5.0, 0.1,             //pose.position.x y z
    0.0, 0.0, 0.0, 1.0,         //pose.orientation.x y z w
    1.0, 1.0, 0.2,              //scale.x y z
    1.0f, 0.0f, 1.0f, 1.0       //color.r g b a
    );
    set_para(&marker[3],
    1.0, 8.0, 0.1,             //pose.position.x y z
    0.0, 0.0, 0.0, 1.0,         //pose.orientation.x y z w
    1.0, 1.0, 0.2,              //scale.x y z
    1.0f, 0.0f, 1.0f, 1.0       //color.r g b a
    );
    set_para(&marker[9],
    0.0, 0.0, 0.1,             //pose.position.x y z
    0.0, 0.0, 0.0, 1.0,         //pose.orientation.x y z w
    1.0, 1.0, 0.2,              //scale.x y z
    1.0f, 0.0f, 1.0f, 1.0       //color.r g b a
    );
    set_para(&marker[1],
    -2.0, 0.0, 0.1,             //pose.position.x y z
    0.0, 0.0, 0.0, 1.0,         //pose.orientation.x y z w
    1.0, 1.0, 0.2,              //scale.x y z
    1.0f, 0.0f, 1.0f, 1.0       //color.r g b a
    );
    while (ros::ok())
    {
        GrayToPseColor(stm32data_msg.voltage01,&marker[1].color.r,&marker[1].color.g,&marker[1].color.b);
        GrayToPseColor(stm32data_msg.voltage09,&marker[9].color.r,&marker[9].color.g,&marker[9].color.b);
        GrayToPseColor(stm32data_msg.voltage03,&marker[3].color.r,&marker[3].color.g,&marker[3].color.b);
        GrayToPseColor(stm32data_msg.voltage02,&marker[2].color.r,&marker[2].color.g,&marker[2].color.b);
        GrayToPseColor(stm32data_msg.voltage04,&marker[4].color.r,&marker[4].color.g,&marker[4].color.b);
        GrayToPseColor(stm32data_msg.voltage08,&marker[8].color.r,&marker[8].color.g,&marker[8].color.b);
        GrayToPseColor(stm32data_msg.voltage05,&marker[5].color.r,&marker[5].color.g,&marker[5].color.b);
        GrayToPseColor(stm32data_msg.voltage13,&marker[13].color.r,&marker[13].color.g,&marker[13].color.b);
        GrayToPseColor(stm32data_msg.voltage06,&marker[6].color.r,&marker[6].color.g,&marker[6].color.b);
        GrayToPseColor(stm32data_msg.voltage07,&marker[7].color.r,&marker[7].color.g,&marker[7].color.b);
        GrayToPseColor(stm32data_msg.voltage12,&marker[12].color.r,&marker[12].color.g,&marker[12].color.b);
        GrayToPseColor(stm32data_msg.voltage11,&marker[11].color.r,&marker[11].color.g,&marker[11].color.b);
        GrayToPseColor(stm32data_msg.voltage10,&marker[10].color.r,&marker[10].color.g,&marker[10].color.b);
        GrayToPseColor(stm32data_msg.voltage00,&marker[0].color.r,&marker[0].color.g,&marker[0].color.b);
        
        
        // GrayToPseColor(color_cnt,&marker[3].color.r,&marker[3].color.g,&marker[3].color.b);
        // if(cnt==3)
        // {
        //     if(color_cnt>=4095) color_cnt=0;
        //     else color_cnt+=4;
        // }
        
        if(pub.getNumSubscribers() < 1)
        {
            mtx.lock();
            ROS_WARN_ONCE("Please create a subscriber to the marker");
            mtx.unlock();
        }
        // while (pub.getNumSubscribers() < 1)
        // {
        //     if (!ros::ok())
        //     {
        //         break;
        //     }
            
        //     // sleep(1);
        // }

        pub.publish(marker[cnt]);
        if(cnt>=13)cnt=0;
        else cnt++;

        // for(i=0;i<14;i++)marker_pub.publish(marker[i]);

        rosrate.sleep();
    }
}

void serial_callback(char* data,int length)
{
    int i=0;
    for(i=0;i<length;i++)
    {
        Queue.push(data[i]);
    }
    // mtx.lock();
    // ROS_INFO("queue size:%d\n",(int)Queue.size());
    // mtx.unlock();
}
void serial_proj(WzSerialportPlus WzSerialport)
{
    if(WzSerialport.open("/dev/ttyUSB0",921600,1,8,'n'))
    {
        getchar();
        WzSerialport.close();
    }
    else 
    {
        ROS_INFO("Serial Open Error!!!!!!!!\n");
        exit(100);
    }
}

void data_pro_proj()
{
    uint8_t i,stat=0;
    uint8_t data_buff[32]={0};
    uint8_t crc_recv[2];
    while(1)
    {
        if(!Queue.empty())
        switch(stat)
        {
            case 0:
                if((uint8_t)Queue.front()==0xFF) stat=1;
                else stat=0;
                Queue.pop();
                break;
            case 1:
                if((uint8_t)Queue.front()==0xEE) stat=2;
                else stat=0;
                Queue.pop();
                break;
            case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9: case 10: 
                case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18: case 19: 
                case 20: case 21: case 22: case 23: case 24: case 25: case 26: case 27: case 28: 
                case 29: case 30: case 31: case 32: case 33: 
                data_buff[stat-2]=(uint8_t)Queue.front();
                Queue.pop();
                stat++;
                break;
            case 34:
                crc_recv[0]=(uint8_t)Queue.front();
                Queue.pop();
                stat=35;
                break;
            case 35:
                crc_recv[1]=(uint8_t)Queue.front();
                Queue.pop();
                stat=36;
                break;
            case 36:
                if((uint8_t)Queue.front()==0xDD) stat=37;
                else stat=0;
                Queue.pop();
                break;
            case 37:
                stat=0;
                if((uint8_t)Queue.front()==0xCC)
                {
                    Queue.pop();
                }
                else 
                {
                    Queue.pop();
                    break;
                }

                if(usMBCRC16(data_buff,32)==crc_recv[0]+(crc_recv[1]<<8))
                {
                    right_cnt++;
                    stm32data_msg.voltage00=data_buff[0]+(data_buff[1]<<8);
                    stm32data_msg.voltage01=data_buff[2]+(data_buff[3]<<8);
                    stm32data_msg.voltage02=data_buff[4]+(data_buff[5]<<8);
                    stm32data_msg.voltage03=data_buff[6]+(data_buff[7]<<8);
                    stm32data_msg.voltage04=data_buff[8]+(data_buff[9]<<8);
                    stm32data_msg.voltage05=data_buff[10]+(data_buff[11]<<8);
                    stm32data_msg.voltage06=data_buff[12]+(data_buff[13]<<8);
                    stm32data_msg.voltage07=data_buff[14]+(data_buff[15]<<8);
                    stm32data_msg.voltage08=data_buff[16]+(data_buff[17]<<8);
                    stm32data_msg.voltage09=data_buff[18]+(data_buff[19]<<8);
                    stm32data_msg.voltage10=data_buff[20]+(data_buff[21]<<8);
                    stm32data_msg.voltage11=data_buff[22]+(data_buff[23]<<8);
                    stm32data_msg.voltage12=data_buff[24]+(data_buff[25]<<8);
                    stm32data_msg.voltage13=data_buff[26]+(data_buff[27]<<8);
                    // mtx.lock();
                    // ROS_INFO("data correct!\r\n");
                    // for(i=0;i<32;i++)
                    // {
                    //     printf("0x%2X ",data_buff[i]);
                    // }
                    // printf("\r\n");
                    // ROS_INFO("crc:0x%4X ",crc_recv[0]+(crc_recv[1]<<8));
                    // mtx.unlock();             
                }
                else
                {
                    wrong_cnt++;
                    mtx.lock();
                    ROS_INFO("right_cnt:%d wrong_cnt:%d error rate:%.1f%%",right_cnt,wrong_cnt,((double)wrong_cnt)/(wrong_cnt+right_cnt)*100);
                    mtx.unlock();
                }
                break;
        }
    }
}

void ros_proj(ros::Publisher pub,ros::Rate rosrate)
{
    mtx.lock();
    ROS_INFO("ros_thread run success\r\n");
    mtx.unlock();
    stm32data_msg.testmsg=123;
    while (ros::ok())
    {
        // 发布消息
		pub.publish(stm32data_msg);
        // mtx.lock();
        // ROS_INFO("Publish stm32data_info:");
       	// ROS_INFO("v00:%4d v01:%4d v02:%4d v03:%4d v04:%4d v05:%4d v06:%4d v07:%4d v08:%4d v09:%4d v10:%4d v11:%4d v12:%4d v13:%4d", 
		// 		  stm32data_msg.voltage00, stm32data_msg.voltage01, stm32data_msg.voltage02, stm32data_msg.voltage03,
        //           stm32data_msg.voltage04, stm32data_msg.voltage05, stm32data_msg.voltage06, stm32data_msg.voltage07,
        //           stm32data_msg.voltage08, stm32data_msg.voltage09, stm32data_msg.voltage10, stm32data_msg.voltage11,
        //           stm32data_msg.voltage12, stm32data_msg.voltage13
        //           );
        // ROS_INFO("right_cnt:%d wrong_cnt:%d error rate:%.1f%%",right_cnt,wrong_cnt,((double)wrong_cnt)/(wrong_cnt+right_cnt)*100);
        // mtx.unlock();
        // 按照循环频率延时
        rosrate.sleep();
    }
}
int main( int argc, char** argv )
{
    uint8_t i=0;

        
    ros::init(argc, argv, "mix_uart_visual");
    ros::NodeHandle n1,n2;

    ros::Publisher stm32data_info_pub = n1.advertise<uart_stm32::stm32data>("/stm32data_info", 38);
    ros::Rate loop_rate1(100);
    WzSerialportPlus wzSerialportPlus;
    wzSerialportPlus.setReceiveCalback(serial_callback);

    ros::Publisher marker_pub = n2.advertise<visualization_msgs::Marker>("visualization_marker", 1);
    ros::Rate loop_rate2(50);
    
    thread serial_thread(serial_proj,wzSerialportPlus);
    thread data_process_thread(data_pro_proj);
    thread ros_thread(ros_proj,stm32data_info_pub,loop_rate1);
    thread visual_thread(visual_proj,marker_pub,loop_rate2);

    serial_thread.join();
    data_process_thread.join();
    ros_thread.join();
    visual_thread.join();

    return 0;
}