#ifndef __DATA_PRTOCOL_H
#define __DATA_PRTOCOL_H
 
struct DataScope
{
	unsigned char DataScope_OutPut_Buffer[42];	   //������֡���ݻ�����
	unsigned char sendNum;//��Ҫ���͵����ݴ�С
	unsigned char channelNum;
};


void DataScope_Get_Channel_Data(float Data,unsigned char Channel);    // дͨ�������� ������֡���ݻ�����

unsigned char DataScope_Data_Generate(unsigned char Channel_Number);  // ����֡�������ɺ��� 
 
 
#endif 



