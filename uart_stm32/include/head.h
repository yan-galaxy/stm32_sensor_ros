#ifndef _HEAD_H
#define _HEAD_H

#include <iostream>
#include <visualization_msgs/Marker.h>


uint16_t usMBCRC16( uint8_t * pucFrame, uint16_t usLen );


void set_para(
visualization_msgs::Marker * sel_marker,
float posx,float posy,float posz,
float orix,float oriy,float oriz,float oriw,
float scax,float scay,float scaz,
float colorR,float colorG,float colorB,float colorAlpha);

void GrayToPseColor(uint16_t grayValue, float *colorR,float *colorG,float *colorB);
void GrayToPseColor_rainbow1(uint16_t grayValue, float *colorR,float *colorG,float *colorB);





#endif