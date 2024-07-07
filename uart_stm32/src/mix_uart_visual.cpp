#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <iostream>
#include <thread>
#include "head.h"
#include "serialPort.hpp"
#include "uart_stm32/stm32data.h"
#include <mutex>
#include <stdlib.h>

bool serial_open;
uint8_t rx_buff[512];
uint8_t rx_stat;
uint8_t rx_num;
uint8_t vol_initial[32];
uint8_t crc_recv[2];
uint8_t zhenwei_recv[2];
const char *dev  = "/dev/ttyUSB0";// ls -l /dev/ttyUSB*
uint32_t right_cnt;
uint32_t wrong_cnt;

uint8_t wrong_data[50000][34];
uint16_t wrong_calc[50000];


uart_stm32::stm32data stm32data_msg;
visualization_msgs::Marker marker[14];
mutex mtx;

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

void serial_proj()
{
    mtx.lock();
    ROS_INFO("serial_thread run success\r\n");
    mtx.unlock();
    serialPort myserial;
    int nread,i;
    serial_open=myserial.OpenPort(dev);
    
    mtx.lock();
    ROS_INFO("serial_open:%d",serial_open);
    mtx.unlock();
    if(serial_open==0)exit(100);

    myserial.setup(B921600,0,8,1,'N'); 

    while (true)
    {
        // nwrite = myserial.writeBuffer( buff, 8);
        nread = myserial.readBuffer( rx_buff, 1);
        switch(rx_stat)
        {
            case 0:
                if(rx_buff[0]==0xFF) rx_stat=1;
                else rx_stat=0;
                break;
            case 1:
                if(rx_buff[0]==0xEE) rx_stat=2;
                else rx_stat=0;
                break;
            case 2:  
                vol_initial[rx_num]=rx_buff[0];
                rx_num++;
                if(rx_num>=32)
                {
                    rx_num=0;
                    rx_stat=3;
                }
                break;
            case 3:
                crc_recv[0]=rx_buff[0];
                rx_stat=4;
                break;
            case 4:
                crc_recv[1]=rx_buff[0];
                rx_stat=5;
                break;
            case 5:
                if(rx_buff[0]==0xDD) rx_stat=6;
                else rx_stat=0;
                break;
            case 6:
                if(rx_buff[0]==0xCC) rx_stat=0;
                else 
                {
                    rx_stat=0;
                    break;
                }
                
            // case 5:
            //     zhenwei_recv[0]=rx_buff[0];
            //     rx_stat=0;

                if(usMBCRC16(vol_initial,32)==crc_recv[0]+(crc_recv[1]<<8))
                {
                    stm32data_msg.voltage00=vol_initial[0]+(vol_initial[1]<<8);
                    stm32data_msg.voltage01=vol_initial[2]+(vol_initial[3]<<8);
                    stm32data_msg.voltage02=vol_initial[4]+(vol_initial[5]<<8);
                    stm32data_msg.voltage03=vol_initial[6]+(vol_initial[7]<<8);
                    stm32data_msg.voltage04=vol_initial[8]+(vol_initial[9]<<8);
                    stm32data_msg.voltage05=vol_initial[10]+(vol_initial[11]<<8);
                    stm32data_msg.voltage06=vol_initial[12]+(vol_initial[13]<<8);
                    stm32data_msg.voltage07=vol_initial[14]+(vol_initial[15]<<8);
                    stm32data_msg.voltage08=vol_initial[16]+(vol_initial[17]<<8);
                    stm32data_msg.voltage09=vol_initial[18]+(vol_initial[19]<<8);
                    stm32data_msg.voltage10=vol_initial[20]+(vol_initial[21]<<8);
                    stm32data_msg.voltage11=vol_initial[22]+(vol_initial[23]<<8);
                    stm32data_msg.voltage12=vol_initial[24]+(vol_initial[25]<<8);
                    stm32data_msg.voltage13=vol_initial[26]+(vol_initial[27]<<8);

                    // for(i=0;i<32;i++)
                    // {
                    //     printf("0x%2X ",vol_data[i]);
                    // }
                    // printf("\r\n");
                    right_cnt++;
                    
                    // printf("crc:0x%4X ",crc_recv[0]+(crc_recv[1]<<8));
                    // printf("\r\n");

                    // mtx.lock();
                    // ROS_INFO("data correct\r\n");
                    // mtx.unlock();
                    // usleep(1000*500);
                }
                else
                {
                    wrong_cnt++;
                    // mtx.lock();
                    // ROS_INFO("\r\n");
                    // ROS_INFO("data ERROR!");
                    // ROS_INFO("recv_data:%4x calc_data:%4x",crc_recv[0]+(crc_recv[1]<<8),usMBCRC16(vol_initial,32));
                    // ROS_INFO("\r\n");

                    // if(wrong_cnt<=50000)
                    // {
                    //     for(i=0;i<32;i++)
                    //     {
                    //         wrong_data[wrong_cnt-1][i]=vol_initial[i];
                    //     }
                    //     wrong_data[wrong_cnt-1][32]=crc_recv[0];
                    //     wrong_data[wrong_cnt-1][33]=crc_recv[1];
                    //     wrong_calc[wrong_cnt-1]=usMBCRC16(vol_initial,32);
                    //     ROS_INFO("%2X %2X %2X %2X %2X %2X %2X %2X %2X %2X %2X %2X %2X %2X %2X %2X %2X %2X %2X %2X %2X %2X %2X %2X %2X %2X %2X %2X %2X %2X %2X %2X", 
                    //             wrong_data[wrong_cnt-1][ 0],wrong_data[wrong_cnt-1][ 1],wrong_data[wrong_cnt-1][ 2],wrong_data[wrong_cnt-1][ 3],
                    //             wrong_data[wrong_cnt-1][ 4],wrong_data[wrong_cnt-1][ 5],wrong_data[wrong_cnt-1][ 6],wrong_data[wrong_cnt-1][ 7],
                    //             wrong_data[wrong_cnt-1][ 8],wrong_data[wrong_cnt-1][ 9],wrong_data[wrong_cnt-1][10],wrong_data[wrong_cnt-1][11],
                    //             wrong_data[wrong_cnt-1][12],wrong_data[wrong_cnt-1][13],wrong_data[wrong_cnt-1][14],wrong_data[wrong_cnt-1][15],
                    //             wrong_data[wrong_cnt-1][16],wrong_data[wrong_cnt-1][17],wrong_data[wrong_cnt-1][18],wrong_data[wrong_cnt-1][19],
                    //             wrong_data[wrong_cnt-1][20],wrong_data[wrong_cnt-1][21],wrong_data[wrong_cnt-1][22],wrong_data[wrong_cnt-1][23],
                    //             wrong_data[wrong_cnt-1][24],wrong_data[wrong_cnt-1][25],wrong_data[wrong_cnt-1][26],wrong_data[wrong_cnt-1][27],
                    //             wrong_data[wrong_cnt-1][28],wrong_data[wrong_cnt-1][29],wrong_data[wrong_cnt-1][30],wrong_data[wrong_cnt-1][31]
                    //             );
                    //     ROS_INFO("wrong_recv_crc:0x%4X",crc_recv[0]+(crc_recv[1]<<8));
                    //     ROS_INFO("wrong_calc_crc:0x%4X",wrong_calc[wrong_cnt-1]);
                    // }
                    // ROS_INFO("right_cnt:%d wrong_cnt:%d error rate:%.1f%%",right_cnt,wrong_cnt,((double)wrong_cnt)/(wrong_cnt+right_cnt)*100);
                    // mtx.unlock();

                    
                }
                break;
        }
        // usleep(400);
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
        mtx.lock();
        // ROS_INFO("Publish stm32data_info:");
       	ROS_INFO("v00:%4d v01:%4d v02:%4d v03:%4d v04:%4d v05:%4d v06:%4d v07:%4d v08:%4d v09:%4d v10:%4d v11:%4d v12:%4d v13:%4d", 
				  stm32data_msg.voltage00, stm32data_msg.voltage01, stm32data_msg.voltage02, stm32data_msg.voltage03,
                  stm32data_msg.voltage04, stm32data_msg.voltage05, stm32data_msg.voltage06, stm32data_msg.voltage07,
                  stm32data_msg.voltage08, stm32data_msg.voltage09, stm32data_msg.voltage10, stm32data_msg.voltage11,
                  stm32data_msg.voltage12, stm32data_msg.voltage13
                  );
        // ROS_INFO("right_cnt:%d wrong_cnt:%d error rate:%.1f%%",right_cnt,wrong_cnt,((double)wrong_cnt)/(wrong_cnt+right_cnt)*100);
        mtx.unlock();
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


    ros::Publisher marker_pub = n2.advertise<visualization_msgs::Marker>("visualization_marker", 1);
    ros::Rate loop_rate2(50);
    
    thread serial_thread(serial_proj);
    thread ros_thread(ros_proj,stm32data_info_pub,loop_rate1);
    thread visual_thread(visual_proj,marker_pub,loop_rate2);

    serial_thread.join();
    ros_thread.join();
    visual_thread.join();

    return 0;
}