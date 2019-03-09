#include "dshot.h"

/*
 * @brief dshot Communicate
 *        
 * */
union
{
   uint8_t sendBuffer[2*ESC_CMD_BUFFER_LEN];
   uint32_t DMA_sendBuffer[ESC_CMD_BUFFER_LEN/2];
}dshotBuffer;
uint32_t ESC_CMD[2*ESC_CMD_BUFFER_LEN]={0};
uint8_t BIT[16];
//每隔 20ms发送一次
void setDshotValue(uint16_t setValue)
{
	setValue = ( (setValue > 2047) ? 2047 : setValue );
	BIT[0]   = (setValue&0x400 ? 1 : 0);
	BIT[1]   = (setValue&0x200 ? 1 : 0);
	BIT[2]   = (setValue&0x100 ? 1 : 0);
	BIT[3]   = (setValue&0x80  ? 1 : 0);
	BIT[4]   = (setValue&0x40  ? 1 : 0);
	BIT[5]   = (setValue&0x20  ? 1 : 0);
	BIT[6]   = (setValue&0x10  ? 1 : 0);
	BIT[7]   = (setValue&0x8   ? 1 : 0);
	BIT[8]   = (setValue&0x4   ? 1 : 0);
	BIT[9]   = (setValue&0x2   ? 1 : 0);
	BIT[10]  = (setValue&0x1   ? 1 : 0);
	BIT[11] =0;
	//getCRC
	BIT[12] = BIT[0]^BIT[4]^BIT[8];
	BIT[13] = BIT[1]^BIT[5]^BIT[9];
	BIT[14] = BIT[2]^BIT[6]^BIT[10];
	BIT[15] = BIT[3]^BIT[7]^BIT[11];
	for(int _i=0;_i<16;_i++)
	{
		dshotBuffer.sendBuffer[2*_i]=(BIT[_i]==1)?ESC_BIT_1:ESC_BIT_0;
		dshotBuffer.sendBuffer[2*_i+1]=(BIT[_i]==1)?ESC_BIT_1:ESC_BIT_0;
	}
}

 
 
 