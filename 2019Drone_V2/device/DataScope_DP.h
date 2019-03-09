#ifndef __DATA_PRTOCOL_H
#define __DATA_PRTOCOL_H
 
struct DataScope
{
	unsigned char DataScope_OutPut_Buffer[42];	   //待发送帧数据缓存区
	unsigned char sendNum;//需要发送的数据大小
	unsigned char channelNum;
};


void DataScope_Get_Channel_Data(float Data,unsigned char Channel);    // 写通道数据至 待发送帧数据缓存区

unsigned char DataScope_Data_Generate(unsigned char Channel_Number);  // 发送帧数据生成函数 
 
 
#endif 



