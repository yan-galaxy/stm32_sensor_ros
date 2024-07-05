#include <ros/ros.h>
#include <iostream>
#include <thread>
#include "head.h"
#include "serialPort.hpp"
#include "uart_stm32/stm32data.h"
#include <mutex>
#include <stdlib.h>
#include <serial/serial.h>

bool serial_open;
uint8_t rx_buff[512];
uint8_t rx_stat;
uint8_t rx_num;
uint8_t vol_initial[32];
uint8_t crc_recv[2];
uint8_t zhenwei_recv[2];
const char *dev  = "/dev/ttyUSB3";// ls -l /dev/ttyUSB*
uint32_t right_cnt;
uint32_t wrong_cnt;

uint8_t wrong_data[50000][34];
uint16_t wrong_calc[50000];

// 初始化learning_topic::Person类型的消息
uart_stm32::stm32data stm32data_msg;
mutex mtx;

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
    while (ros::ok())
    {
        // 发布消息
		pub.publish(stm32data_msg);
        mtx.lock();
        // ROS_INFO("Publish stm32data_info:");
       	// ROS_INFO("%d %d %d %d %d %d %d %d %d %d %d %d %d %d ", 
		// 		  stm32data_msg.voltage00, stm32data_msg.voltage01, stm32data_msg.voltage02, stm32data_msg.voltage03,
        //           stm32data_msg.voltage04, stm32data_msg.voltage05, stm32data_msg.voltage06, stm32data_msg.voltage07,
        //           stm32data_msg.voltage08, stm32data_msg.voltage09, stm32data_msg.voltage10, stm32data_msg.voltage11,
        //           stm32data_msg.voltage12, stm32data_msg.voltage13
        //           );
        ROS_INFO("right_cnt:%d wrong_cnt:%d error rate:%.1f%%",right_cnt,wrong_cnt,((double)wrong_cnt)/(wrong_cnt+right_cnt)*100);
        mtx.unlock();
        // 按照循环频率延时
        rosrate.sleep();
    }
}
int main(int argc, char **argv)
{

    // ROS节点初始化
    ros::init(argc, argv, "stm32data_publisher");

    // 创建节点句柄
    ros::NodeHandle n;

    // 创建一个Publisher，发布名为/person_info的topic，消息类型为learning_topic::Person，队列长度10
    ros::Publisher stm32data_info_pub = n.advertise<uart_stm32::stm32data>("/stm32data_info", 38);
    
    
    ROS_INFO("ROS init success\r\n");
    // 设置循环的频率
    ros::Rate loop_rate(500);

    thread serial_thread(serial_proj);
    thread ros_thread(ros_proj,stm32data_info_pub,loop_rate);

    serial_thread.join();
    ros_thread.join();

    return 0;
}
